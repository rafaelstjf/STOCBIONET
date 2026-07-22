#include <adwaita.h>
#include <gtk/gtk.h>

#include <algorithm>
#include <cstdlib>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "DirectMethod.hpp"
#include "FirstReactionMethod.hpp"
#include "Model.hpp"
#include "ModifiedNextReactionMethod.hpp"
#include "NextReactionMethod.hpp"
#include "NextReactionMethodCompact.hpp"
#include "OptimizedDirectMethod.hpp"
#include "RejectionMethod.hpp"
#include "SimplifiedNextReactionMethod.hpp"
#include "SortingDirectMethod.hpp"

namespace
{
struct PlotPoint
{
    double time;
    std::vector<double> values;
};

struct GuiState
{
    GtkWidget *file_entry;
    GtkWidget *method_dropdown;
    GtkWidget *initial_entry;
    GtkWidget *maximum_entry;
    GtkWidget *seed_entry;
    GtkWidget *run_button;
    GtkWidget *drawing_area;
    GtkWidget *status_label;
    std::mutex mutex;
    std::vector<PlotPoint> points;
    bool running = false;
    bool finished = false;
    std::string status;
};

SSA *allocateGuiSimulation(const std::string &op)
{
    if (op == "DM") return new DirectMethod();
    if (op == "SDM") return new SortingDirectMethod();
    if (op == "ODM") return new OptimizedDirectMethod();
    if (op == "FRM") return new FirstReactionMethod();
    if (op == "NRM") return new NextReactionMethod();
    if (op == "NRMC") return new NextReactionMethodCompact();
    if (op == "MNRM") return new ModifiedNextReactionMethod();
    if (op == "SNRM") return new SimplifiedNextReactionMethod();
    if (op == "RM-OL" || op == "RM-H" || op == "RM-CL" || op == "RM-HT")
    {
        RejectionMethod *method = new RejectionMethod();
        if (op == "RM-OL") method->setDelayStructure(1);
        if (op == "RM-H") method->setDelayStructure(2);
        if (op == "RM-CL") method->setDelayStructure(3);
        if (op == "RM-HT") method->setDelayStructure(4);
        return method;
    }
    return nullptr;
}

std::string activeMethod(GtkWidget *dropdown)
{
    static const char *methods[] = {"DM", "ODM", "SDM", "FRM", "NRM", "NRMC", "MNRM", "SNRM", "RM-OL", "RM-H", "RM-CL", "RM-HT"};
    guint selected = gtk_drop_down_get_selected(GTK_DROP_DOWN(dropdown));
    if (selected >= G_N_ELEMENTS(methods))
        return "DM";
    return methods[selected];
}

std::vector<PlotPoint> snapshotPoints(GuiState *state, std::string &status, bool &running, bool &finished)
{
    std::lock_guard<std::mutex> lock(state->mutex);
    status = state->status;
    running = state->running;
    finished = state->finished;
    return state->points;
}

void drawChart(GtkDrawingArea *, cairo_t *cr, int width, int height, gpointer user_data)
{
    GuiState *state = static_cast<GuiState *>(user_data);
    std::string status;
    bool running = false;
    bool finished = false;
    std::vector<PlotPoint> points = snapshotPoints(state, status, running, finished);

    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);

    const double left = 56.0;
    const double right = 18.0;
    const double top = 18.0;
    const double bottom = 42.0;
    const double plotWidth = std::max(1.0, width - left - right);
    const double plotHeight = std::max(1.0, height - top - bottom);

    cairo_set_source_rgb(cr, 0.88, 0.88, 0.88);
    cairo_rectangle(cr, left, top, plotWidth, plotHeight);
    cairo_stroke(cr);

    cairo_set_source_rgb(cr, 0.35, 0.35, 0.35);
    cairo_move_to(cr, left, top + plotHeight);
    cairo_line_to(cr, left + plotWidth, top + plotHeight);
    cairo_move_to(cr, left, top);
    cairo_line_to(cr, left, top + plotHeight);
    cairo_stroke(cr);

    if (points.empty())
    {
        cairo_set_source_rgb(cr, 0.25, 0.25, 0.25);
        cairo_move_to(cr, left + 20, top + 34);
        cairo_show_text(cr, "Execute uma simulacao para ver o grafico em tempo real.");
        return;
    }

    double minTime = points.front().time;
    double maxTime = points.back().time;
    double maxValue = 1.0;
    int speciesCount = 0;
    for (const PlotPoint &point : points)
    {
        speciesCount = std::max(speciesCount, static_cast<int>(point.values.size()));
        for (double value : point.values)
            maxValue = std::max(maxValue, value);
    }
    if (maxTime <= minTime)
        maxTime = minTime + 1.0;

    const double colors[][3] = {
        {0.12, 0.47, 0.71}, {1.00, 0.50, 0.05}, {0.17, 0.63, 0.17},
        {0.84, 0.15, 0.16}, {0.58, 0.40, 0.74}, {0.55, 0.34, 0.29}};

    for (int specie = 0; specie < speciesCount; ++specie)
    {
        bool hasPoint = false;
        cairo_set_source_rgb(cr, colors[specie % 6][0], colors[specie % 6][1], colors[specie % 6][2]);
        cairo_set_line_width(cr, 1.8);
        for (const PlotPoint &point : points)
        {
            if (specie >= static_cast<int>(point.values.size()))
                continue;
            double x = left + ((point.time - minTime) / (maxTime - minTime)) * plotWidth;
            double y = top + plotHeight - (point.values[specie] / maxValue) * plotHeight;
            if (!hasPoint)
            {
                cairo_move_to(cr, x, y);
                hasPoint = true;
            }
            else
            {
                cairo_line_to(cr, x, y);
            }
        }
        cairo_stroke(cr);
    }

    cairo_set_source_rgb(cr, 0.20, 0.20, 0.20);
    cairo_move_to(cr, left, height - 16);
    std::stringstream xLabel;
    xLabel << "tempo: " << minTime << " - " << maxTime << " | valor max: " << maxValue;
    cairo_show_text(cr, xLabel.str().c_str());
}

gboolean refreshChart(gpointer user_data)
{
    GuiState *state = static_cast<GuiState *>(user_data);
    std::string status;
    bool running = false;
    bool finished = false;
    snapshotPoints(state, status, running, finished);
    gtk_label_set_text(GTK_LABEL(state->status_label), status.c_str());
    gtk_widget_queue_draw(state->drawing_area);
    gtk_widget_set_sensitive(state->run_button, !running);
    return running && !finished ? G_SOURCE_CONTINUE : G_SOURCE_REMOVE;
}

void appendPoint(GuiState *state, long double time, const double *values, int size)
{
    std::lock_guard<std::mutex> lock(state->mutex);
    PlotPoint point;
    point.time = static_cast<double>(time);
    point.values.assign(values, values + size);
    state->points.push_back(point);
    if (state->points.size() > 2000)
        state->points.erase(state->points.begin(), state->points.begin() + 250);
    std::stringstream status;
    status << "Simulando... t=" << point.time << " | pontos=" << state->points.size();
    state->status = status.str();
}

void runSimulation(GtkButton *, gpointer user_data)
{
    GuiState *state = static_cast<GuiState *>(user_data);
    std::string filename = gtk_editable_get_text(GTK_EDITABLE(state->file_entry));
    std::string methodName = activeMethod(state->method_dropdown);
    double initialTime = std::atof(gtk_editable_get_text(GTK_EDITABLE(state->initial_entry)));
    double maximumTime = std::atof(gtk_editable_get_text(GTK_EDITABLE(state->maximum_entry)));
    const char *seedText = gtk_editable_get_text(GTK_EDITABLE(state->seed_entry));
    long int seed = seedText[0] == '\0' ? -1 : std::atol(seedText);

    if (filename.empty())
    {
        std::lock_guard<std::mutex> lock(state->mutex);
        state->status = "Selecione um arquivo de modelo SBML/XML ou STOCBIONET.";
        gtk_label_set_text(GTK_LABEL(state->status_label), state->status.c_str());
        return;
    }

    {
        std::lock_guard<std::mutex> lock(state->mutex);
        state->points.clear();
        state->running = true;
        state->finished = false;
        state->status = "Carregando modelo...";
    }
    gtk_widget_set_sensitive(state->run_button, FALSE);
    g_timeout_add(100, refreshChart, state);

    std::thread([state, filename, methodName, initialTime, maximumTime, seed]() {
        Model model;
        model.loadModel(filename);
        if (!model.isModelLoaded())
        {
            std::lock_guard<std::mutex> lock(state->mutex);
            state->status = "Erro ao carregar o modelo.";
            state->running = false;
            state->finished = true;
            return;
        }

        SSA *simulation = allocateGuiSimulation(methodName);
        if (simulation == nullptr)
        {
            std::lock_guard<std::mutex> lock(state->mutex);
            state->status = "Metodo invalido.";
            state->running = false;
            state->finished = true;
            return;
        }

        simulation->onBatch();
        simulation->setProgressCallback([state](long double time, const double *values, int size) {
            appendPoint(state, time, values, size);
        });
        simulation->perform(&model, maximumTime, initialTime, seed);

        std::stringstream result;
        result << "Simulacao concluida | Metodo: " << methodName
               << " | Seed: " << simulation->getSeed()
               << " | Reacoes: " << simulation->getNumberReacExecuted()
               << " | Reacoes/s: " << simulation->getReacPerSecond()
               << " | Tempo gasto: " << simulation->getTimeSpent() << " s";
        delete simulation;

        std::lock_guard<std::mutex> lock(state->mutex);
        state->status = result.str();
        state->running = false;
        state->finished = true;
    }).detach();
}

void activate(GtkApplication *app, gpointer)
{
    GtkWindow *window = GTK_WINDOW(adw_application_window_new(app));
    gtk_window_set_title(window, "STOCBIONET");
    gtk_window_set_default_size(window, 1000, 720);

    GtkWidget *content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_widget_set_margin_top(content, 18);
    gtk_widget_set_margin_bottom(content, 18);
    gtk_widget_set_margin_start(content, 18);
    gtk_widget_set_margin_end(content, 18);
    adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), content);

    GuiState *state = new GuiState();
    state->file_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(state->file_entry), "arquivo .xml/.sbml/.txt");
    gtk_box_append(GTK_BOX(content), state->file_entry);

    const char *methods[] = {"DM", "ODM", "SDM", "FRM", "NRM", "NRMC", "MNRM", "SNRM", "RM-OL", "RM-H", "RM-CL", "RM-HT", nullptr};
    state->method_dropdown = gtk_drop_down_new_from_strings(methods);
    gtk_box_append(GTK_BOX(content), state->method_dropdown);

    state->initial_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(state->initial_entry), "tempo inicial");
    gtk_editable_set_text(GTK_EDITABLE(state->initial_entry), "0");
    gtk_box_append(GTK_BOX(content), state->initial_entry);

    state->maximum_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(state->maximum_entry), "tempo maximo");
    gtk_editable_set_text(GTK_EDITABLE(state->maximum_entry), "10");
    gtk_box_append(GTK_BOX(content), state->maximum_entry);

    state->seed_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(state->seed_entry), "seed opcional");
    gtk_box_append(GTK_BOX(content), state->seed_entry);

    state->run_button = gtk_button_new_with_label("Executar simulacao");
    g_signal_connect(state->run_button, "clicked", G_CALLBACK(runSimulation), state);
    gtk_box_append(GTK_BOX(content), state->run_button);

    state->status_label = gtk_label_new("Pronto para simular.");
    gtk_label_set_xalign(GTK_LABEL(state->status_label), 0.0);
    gtk_box_append(GTK_BOX(content), state->status_label);

    state->drawing_area = gtk_drawing_area_new();
    gtk_widget_set_vexpand(state->drawing_area, TRUE);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(state->drawing_area), drawChart, state, nullptr);
    gtk_box_append(GTK_BOX(content), state->drawing_area);

    gtk_window_present(window);
}
}

int main(int argc, char **argv)
{
    g_autoptr(AdwApplication) app = adw_application_new("br.uf.stocbionet.Stocbionet", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), nullptr);
    return g_application_run(G_APPLICATION(app), argc, argv);
}
