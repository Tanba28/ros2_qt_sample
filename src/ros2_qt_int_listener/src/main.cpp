#include "mainwindow.h"

#include <QApplication>

#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

using std::placeholders::_1;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */


class Gui{
    public:
        Gui(int &argc, char **argv){
            a = new QApplication(argc, argv);
            w = new MainWindow();
            w->show();
        }

        void processEvents(){
            a->processEvents();
        }
        bool isVisible(){
            return w->isVisible();
        }
        void setNum(int num){
            w->setNum(num);
        }

    private:
        QApplication *a;
        MainWindow *w;
};


class QtIntListener : public rclcpp::Node
{
    public: 
        QtIntListener(std::shared_ptr<Gui> _gui)
        : Node("qt_int_listener"),gui(_gui){
        subscription_ = this->create_subscription<std_msgs::msg::Int64>("topic", 10,std::bind(&QtIntListener::topic_callback,this,_1));
        }


    private:
        void topic_callback(const std_msgs::msg::Int64 &msg){
            gui->setNum(msg.data);
            RCLCPP_INFO(this->get_logger(), "I heard:%ld", msg.data);
        }
        rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_;
        std::shared_ptr<Gui> gui;
};

int main(int argc, char *argv[]){
    std::shared_ptr<Gui> gui = std::make_shared<Gui>(argc, argv);

    rclcpp::init(argc, argv);
    std::shared_ptr<QtIntListener> node = std::make_shared<QtIntListener>(gui);

    while(gui->isVisible()){
        rclcpp::spin_some(node);
        gui->processEvents();
    }

    rclcpp::shutdown();
    return 0;
}
