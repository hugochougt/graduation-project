#include <gtk/gtk.h>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

Mat frame, outImage;

volatile bool threadRun;
mutex myMutex;
thread myThread;

Gtk::Window *mainWindow;
Gtk::Image *drawingImage;
Glib::Dispatcher dispatcher;

void run()
{
    threadRun = true;
    VideoCapture capture;

    while(threadRun)
    {
        myMutex.lock();
        capture >> fram;
        myMutex.unlock();
        dispatcher.emit();
    }

}

int main(int argc, char** argv)
{
    gdk_threads_init();

    Gtk::Main gtkMain(argc, argv);
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("some_ui_definition.glade");
    builder->get_widget("MainWindow", mainWindow);
    builder->get_widget("DrawingImage", drawingImage);

    dispatcher.connect([&]() {
            myMutex.lock();
            cvtColor(frame, outImage, CV_BGR2RGB);
            drawingImage->set(Gdk::Pixbuf::create_from_data(outImage.data, Gdk::COLORSPACE_RGB, false, 8, outImage.cols, outImage.rows, outImage.step1o));
            drawingImage->queue_draw();
            myMutex.unlock();
            });

    myThread = thread(&run);
    gtkMain.run(*mainWindow);

    gdk_threads_leave();

    return 0;
}
