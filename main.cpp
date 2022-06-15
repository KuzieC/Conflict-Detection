#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <Windows.h>
#include <math.h>
using namespace std;
/** Use to init the clock */
#define TIMER_INIT           \
    LARGE_INTEGER frequency; \
    LARGE_INTEGER t1, t2;    \
    double elapsedTime = 0;  \
    QueryPerformanceFrequency(&frequency);

/** Use to start the performance timer */
#define TIMER_START QueryPerformanceCounter(&t1);

/** Use to stop the performance timer and output the result to the standard stream. Less verbose than \c TIMER_STOP_VERBOSE */
#define TIMER_STOP                                                         \
    QueryPerformanceCounter(&t2);                                          \
    elapsedTime = (float)(t2.QuadPart - t1.QuadPart) / frequency.QuadPart; \
    // std::cout << elapsedTime;

int main()
{
    int num;
    cout << "enter the number of planes"
         << "\n";
    cin >> num;
    int epoch = 100;
    int length_airspace = 1000;
    int width_airspace = 1000;
    int height_airspace = 11;
    int length_unit = 20;
    int width_unit = 20;
    int ck = 1;
    int height_unit = 1;
    int min_speed = 150;
    int max_speed = 250;
    double totaltime = 0;
    int aircraft_length[num];
    int aircraft_width[num];
    int aircraft_height[num];
    int aircraft_dir_x[num];
    int aircraft_dir_y[num];
    int aircraft_dir_z[num];
    int aircraft_speed[num];
    // int danger_x[num];
    // int danger_y[num];
    int initial_x = 0;
    int initial_y = 0;
    int initial_z = 7;
    int s = 0;
    int collisioncount = 0;
    srand(time(NULL));
    while (s < num)
    {

        aircraft_length[s] = (rand() % length_airspace + 0);

        aircraft_width[s] = (rand() % width_airspace + 0);

        aircraft_height[s] = (rand() % (height_airspace - initial_z) + initial_z);

        aircraft_speed[s] = (rand() % (max_speed - min_speed) + min_speed);

        aircraft_dir_x[s] = (rand() % (length_airspace * 2) + (length_airspace * -1));

        aircraft_dir_y[s] = (rand() % (width_airspace * 2) + (width_airspace * -1));

        aircraft_dir_z[s] = (rand() % (height_airspace * 2) + (height_airspace * -1));

        s = s + 1;
    }
    int x = initial_x;
    int y = initial_y;
    int z = initial_z;
    int planecount = 0;
    int num_x = int(length_airspace / length_unit);
    int num_y = int(width_airspace / width_unit);
    int num_z = int((height_airspace - initial_z) / height_unit);
    list<int> unitblock[num_x][num_y][num_z];
    for (int i = 0; i < num_x; i++)
    {
        for (int j = 0; j < num_y; j++)
        {
            for (int kt = 0; kt < num_z; kt++)
            {
                unitblock[i][j][kt] = {0};
            }
        }
    }
    for (int g = 0; g < epoch; g++)
    {
        // total frame number
        TIMER_INIT
        TIMER_START
        list<int> danger_x = {};
        list<int> danger_y = {};
       
        for (int i = 0; i < num_x; i++)
        {
            for (int j = 0; j < num_y; j++)
            {
                for (int k = 0; k < num_z; k++)
                {
                    unitblock[i][j][k] = {0};
                }
            }
        }
        for (int i = 0; i < num; i++)
        { // update plane position
            if ((aircraft_length[i] != -999) and (aircraft_width[i] != -999))
            {
                aircraft_length[i] = aircraft_length[i] + aircraft_dir_x[i] * 0.001;
                aircraft_width[i] = aircraft_width[i] + aircraft_dir_y[i] * 0.001;
                aircraft_height[i] = aircraft_height[i] + aircraft_dir_z[i] * 0.001;
            }
        }
        planecount = 0;
        while (planecount < num)
        { // check collision
            if (aircraft_length[planecount] > length_airspace or aircraft_length[planecount] < 0 or aircraft_width[planecount] > width_airspace or aircraft_width[planecount] < 0)
            {
                aircraft_length[planecount] = -999;
                aircraft_width[planecount] = -999;
            }
            else
            {
                int tem_x = int(aircraft_length[planecount] / length_unit);
                int tem_y = int(aircraft_width[planecount] / width_unit);
                int tem_z = int((aircraft_height[planecount] - initial_z) / height_unit);
                for (int i = tem_x - 1; i <= tem_x + 1; ++i)
                {
                    if (i < 0)
                    {
                        i = 0;
                    }
                    if (i >= length_airspace / length_unit)
                    {
                        break;
                    }
                    for (int j = tem_y - 1; j <= tem_y + 1; ++j)
                    {
                        if (j < 0)
                        {
                            j = 0;
                        }
                        if (i >= width_airspace / width_unit)
                        {
                            break;
                        }
                        for (int k = tem_z - 1; k <= tem_z + 1; ++k)
                        {
                            if (k < 0)
                            {
                                k = 0;
                            }
                            if (i >= height_airspace / height_unit)
                            {
                                break;
                            }
                            int temUpperlim_x = i * length_unit + length_unit * (ck * 0.5);
                            int temLowerlim_x = i * length_unit - length_unit * (ck * 0.5);
                            int temUpperlim_y = j * width_unit + width_unit * (ck * 0.5);
                            int temLowerlim_y = j * width_unit - width_unit * (ck * 0.5);
                            int temUpperlim_z = k * height_unit + height_unit * (ck * 0.5);
                            int temLowerlim_z = k * height_unit - height_unit * (ck * 0.5);
                            if (temLowerlim_x <= aircraft_length[planecount] <= temUpperlim_x and temLowerlim_y <= aircraft_width[planecount] <= temUpperlim_y and temLowerlim_z <= aircraft_height[planecount] <= temUpperlim_z)
                            {
                                unitblock[i][j][k].push_back(planecount);
                                if ((unitblock[i][j][k]).size() > 2)
                                {
                                    int repeat = (unitblock[i][j][k]).size();
                                    for (int ii = 0; ii < repeat - 2; ii++)
                                    {
                                        int hp = 0;
                                        int compareplane;
                                        for (list<int>::iterator n = unitblock[ii][j][k].begin(); n != unitblock[ii][j][k].end(); ++n)
                                        {
                                            if (hp != ii + 1)
                                            {
                                                hp = hp + 1;
                                            }
                                            else
                                            {
                                                compareplane = *n;
                                                int disp_x = pow(aircraft_length[compareplane] - aircraft_length[planecount], 2);
                                                int disp_y = pow(aircraft_width[compareplane] - aircraft_width[planecount], 2);
                                                int disp_z = pow(aircraft_height[compareplane] - aircraft_height[planecount], 2);
                                                float dis1 = sqrt((disp_x + disp_y + disp_z) * 1.0);
                                                int moved1_x = aircraft_length[planecount] + aircraft_dir_x[planecount] * 0.001;
                                                int moved1_y = aircraft_width[planecount] + aircraft_dir_y[planecount] * 0.001;
                                                int moved1_z = aircraft_height[planecount] + aircraft_dir_z[planecount] * 0.001;
                                                int moved2_x = aircraft_length[compareplane] + aircraft_dir_x[compareplane] * 0.001;
                                                int moved2_y = aircraft_width[compareplane] + aircraft_dir_y[compareplane] * 0.001;
                                                int moved2_z = aircraft_height[compareplane] + aircraft_dir_z[compareplane] * 0.001;
                                                float dis2 = sqrt(((moved1_x - moved2_x) ^ 2 + (moved1_y - moved2_y) ^ 2 + (moved1_z - moved2_z) ^ 2) * 1.0);
                                                if (dis1 > dis2)
                                                {
                                                    // danger_x.append(aircraft_length[planecount])
                                                    // danger_x.append(aircraft_length[compareplane])
                                                    // danger_y.append(aircraft_width[planecount])
                                                    // danger_y.append(aircraft_width[compareplane])
                                                    collisioncount = collisioncount + 1;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            planecount = planecount + 1;
        }
        cout << "number of collision " << collisioncount << "\n";
        collisioncount = 0;
        TIMER_STOP
        totaltime = totaltime + elapsedTime;
    }
    cout << "average caluculation time is " << totaltime /epoch;
}