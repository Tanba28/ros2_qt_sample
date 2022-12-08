#include "mainwindow.h"

#include <QApplication>

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

using namespace std::chrono_literals;

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

        int getNum(){
            return w->getNum();
        }

    private:
        QApplication *a;
        MainWindow *w;
};

class QtIntSender : public rclcpp::Node
{
    public:
        QtIntSender(std::shared_ptr<Gui> _gui)
        : Node("qt_int_sender"),gui(_gui){
            publisher_ = this->create_publisher<std_msgs::msg::Int64>("topic", 10);
        }
        void publish(int data){
            auto message = std_msgs::msg::Int64();
            message.data = data;
            publisher_->publish(message);
        }

    private:
        rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
        std::shared_ptr<Gui> gui;
};

int main(int argc, char *argv[])
{
    std::shared_ptr<Gui> gui = std::make_shared<Gui>(argc, argv);

    rclcpp::init(argc, argv);
    std::shared_ptr<QtIntSender> node = std::make_shared<QtIntSender>(gui);

    long int data;
    while(gui->isVisible()){
        data = gui->getNum();
        node->publish(data);
        RCLCPP_INFO(node->get_logger(),"I send:%ld\n",data);
        gui->processEvents();
        rclcpp::sleep_for(10ms);
    }
    
    rclcpp::shutdown();
    return 0;
}
