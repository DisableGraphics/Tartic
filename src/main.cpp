#include "giomm/application.h"
#include "glibmm/refptr.h"
#include "gtkmm/application.h"
#include "gtkmm/scrolledwindow.h"
#include "gtkmm/textbuffer.h"
#include "gtkmm/textview.h"
#include "gtkmm/window.h"
#include <fstream>
#include <cstddef>
#include <gtkmm.h>
#include <iostream>
#include <fstream>
#include <filesystem>

std::string fileName;
namespace fs = std::filesystem;

std::string load(){
    fs::path f{fileName};    
    if(fs::exists(f)){
        std::ostringstream sstr;
        std::ifstream file;
        file.open(fileName);
        sstr << file.rdbuf();
        file.close();
        return sstr.str();
    } else {
        return "";
    }
}
bool save(GdkEventAny* event, Gtk::TextView& textView, Glib::RefPtr<Gtk::Application> app){
    std::ofstream file;
    file.open(fileName);

    file << textView.get_buffer()->get_text();

    file.close();
    app->quit();
    return true;
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        if(argc < 2){
            std::cout << "Error: file not specified\n";
        } else {
            std::cout << "Error: too many files specified\n";
        }
        return 1;
    } else {
         
        fileName = argv[1];

        argc--;
        argv[1] = NULL;

        Glib::RefPtr<Gtk::Application> app = Gtk::Application::create( argc, argv, "" );

        Gtk::Window window;
        window.set_border_width(2);
        Gtk::TextView textView;

        Gtk::ScrolledWindow scrollWindow;

        scrollWindow.set_size_request(400, 300);

        Glib::ustring buffer_text{load()};

        textView.get_buffer()->set_text(buffer_text);

        window.signal_delete_event().connect(sigc::bind<Gtk::TextView&, Glib::RefPtr<Gtk::Application>>(sigc::ptr_fun(&save), textView, app));

        scrollWindow.add(textView);

        window.add(scrollWindow);

        window.show_all();

        return app->run(window);
    }
}