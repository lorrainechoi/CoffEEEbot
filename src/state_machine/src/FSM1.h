#ifndef FSM_H
#define FSM_H

const int bufferSize=1000;

class FSM{
private:
    ros::Publisher questionPub;
    ros::Publisher privacyPub;
    ros::Subscriber nameSub;
    ros::Subscriber answerSub;

    coffee coffEEEbot[5];

    int currState;
    int oldState;

    int num_out_of_stock;
    int out_of_stock[5];

    string name;

public:
    FSM(ros::NodeHandle& n) :
        currState(1), oldState(1), num_out_of_stock(0)
    {
        coffEEEbot[0].type="Cappuccino";
        coffEEEbot[1].type="Cafe Au Lait";
        coffEEEbot[2].type="Caramel Latte";
        coffEEEbot[3].type="Tea Latte";
        coffEEEbot[4].type="Lungo Decaf";

        coffEEEbot[0].stock=1;
        coffEEEbot[1].stock=1;
        coffEEEbot[2].stock=1;
        coffEEEbot[3].stock=1;
        coffEEEbot[4].stock=1;
	
	out_of_stock[0]=0;
	out_of_stock[1]=0;
	out_of_stock[2]=0;
	out_of_stock[3]=0;
	out_of_stock[4]=0;
	
        questionPub = n.advertise<std_msgs::String>("question", bufferSize);
        privacyPub= n.advertise<std_msgs::String>("privacy", bufferSize);
        nameSub = n.subscribe("name", bufferSize, &FSM::nameCallback, this);
        answerSub = n.subscribe("answer", bufferSize, &FSM::answerCallback, this);
    }

    void nameCallback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("Customer name: %s", msg->data.c_str());
    name=msg->data.c_str();
    currState=2;    
    fsm();
    }
    void answerCallback(const std_msgs::Int32::ConstPtr& msg){
    oldState=currState;
    state_change(msg->data);
    fsm();
    }
    void state_change(int);
    void fsm();
    void state1();
    void state2();
    void state3();
    void state4();
    void state5();
    void state6();
    void state7();
    void state8();
    void state9();
    void state10();
    void state11();
    void state12();
};

void FSM:: state_change(int input){
    int next=currState;
    if(currState==2||currState==8||currState==11){
        if(1<=input<=7){
            next=input+2;
        }
        else
            ROS_INFO("INVALID INPUT");
    }

    else if(3<=currState<=7){
        if(input==0){
            next=10;
        }
        else if(input==1){
            next=11;
        }
        else
            ROS_INFO("INVALID INPUT");
    }

    else if(currState==9||currState==10){
        next=12;
    }

    else if(currState==12){
        next=1;
    }

    else
        ROS_INFO("INVALID Current state");

    if (next>=13||next<=0){
        ROS_INFO("INVALID Next state");
        next=currState;
    }

    ROS_INFO("State Transitioning from %d to %d",currState,next);
    
    oldState=currState;
    currState=next;
return ;
}

void FSM::fsm(){
    ROS_INFO("Current state: %d\n",currState);

    switch(currState){
        case 1:
            state1();
            break;
        case 2:
            state2();
            break;
        case 3:
            state3();
            break;
        case 4:
            state4();
            break;
        case 5:
            state5();
            break;
        case 6:
            state6();
            break;
        case 7:
            state7();
            break;
        case 8:
            state8();
            break;
        case 9:
            state9();
            break;
        case 10:
            state10();
            break;
        case 11:
            state11();
            break;
        case 12:
            state12();
            break;
    }
    
    return;
}

void FSM::state1(){
    //say hello
    //record response
    //send name to data base

    std_msgs::String msg;

    std::stringstream ss;

    ss<<"Hello I am CoffEEEbot, what's your name?\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}

void FSM::state2(){
    //coffee selection
    //what do you want?
    int stock=0;

    num_out_of_stock=check_stock(coffEEEbot, out_of_stock);

    stock=gen_stock_code(out_of_stock);

    std_msgs::String msg;

    std::stringstream ss;

    ss<< name<<", what do you want?, 1, "<<stock<<"\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}

void FSM::state3(){
    //coffee selection
    //what do you want?
    std_msgs::String msg;

    std::stringstream ss;

    ss<<"You want a Cappuccino?, 2, 0\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}

void FSM::state4(){
    //coffee selection
    //what do you want?
    std_msgs::String msg;

    std::stringstream ss;

    ss<<"You want a Cafe Au Lait?, 2, 0\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}

void FSM::state5(){
    //coffee selection
    //what do you want?
    std_msgs::String msg;

    std::stringstream ss;

    ss<<"You want a Caramel Latte?, 2, 0\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}


void FSM::state6(){
    //coffee selection
    //what do you want?
    std_msgs::String msg;

    std::stringstream ss;

    ss<<"You want a Tea Latte?, 2, 0\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}

void FSM::state7(){
    //coffee selection
    //what do you want?
    std_msgs::String msg;

    std::stringstream ss;

    ss<<"You want a Lungo Decaf?, 2, 0\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}


void FSM::state8(){
    //coffee introduction
    //what do you want?
    int stock=0; 
	
    num_out_of_stock=check_stock(coffEEEbot, out_of_stock);

    stock=gen_stock_code(out_of_stock);

    std_msgs::String msg;

    std::stringstream ss;

    ss<<"1 Cappuccino\nI am Cappuccino.\n2 Cafe Au Lait\nI am Cafe Au Lait.\n3 Caramel Latte\nI am Caramel Latte.\n4 Tea Latte\nI am Tea Latte.\n5 Lungo decaf\nI am Lungo decaf.\nWhat would you like?"<<", 1"<<", "<<stock<<"\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}

void FSM::state9(){
    //privacy
    //remembered?

    std_msgs::String msg;

    std::stringstream ss;

    ss <<"Would you like to be remembered? y/n\n"<<", 2, 0\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}



void FSM::state10(){
    //tutorial
    std_msgs::String msg;

    std::stringstream ss;

    ss <<"Watch out hot water!\nPLAY TUTORIAL VIDEO\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}

void FSM::state11(){
    //error state
    //sorry, what do you want?
    int stock=0;

    num_out_of_stock=check_stock(coffEEEbot, out_of_stock);

    stock=gen_stock_code(out_of_stock);

    std_msgs::String msg;

    std::stringstream ss;

    ss<<"I am really sorry, could you repeat your choice?, 1, "<<stock<<"\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    return;
}

void FSM::state12(){
    //tutorial
    std_msgs::String msg;

    std::stringstream ss;

    ss <<"Thank you for coming!\n";
    msg.data =ss.str();

    ROS_INFO("%s",msg.data.c_str());

    questionPub.publish(msg);

    for(int i=0;i<5;i++){
        ROS_INFO("%s %d", coffEEEbot[i].type.c_str(), coffEEEbot[i].stock);
    }
    return;
}

#endif // FSM_H
