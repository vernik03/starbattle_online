
#include "boost_asio.h"

#include <iostream>
#include <random>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <iterator>
#include <regex>
#include <sstream>
#include <thread>

#include "Framework.h"
#include "GlobalVariables.h"
#include "MapCreator.h"
#include "InfoToSend.h"

class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		//
		width = WINDOW_WIDTH;
		height = WINDOW_HEIGHT;
		if (WINDOW_WIDTH == 0 && WINDOW_HEIGHT == 0)
			fullscreen = true;
		else
			fullscreen = false;
	}

	virtual bool Init() {

		map_manager = std::make_unique<MapCreator>();
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		showCursor(false);

		map_manager->DrawAll();
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		keep_info->SetCoords(x, y);

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		keep_info->SetClick(button, isReleased);
	}

	virtual void onKeyPressed(FRKey k) {
		keep_info->SetKey(k);
	}

	virtual void onKeyReleased(FRKey k) {
	}

	virtual const char* GetTitle() override
	{
		return "asteroids";
	}

	void ParseData() {

	}
private:

	///
	std::unique_ptr<MapCreator> map_manager;
	std::unique_ptr<InfoToSend> keep_info;
	/// 


};



int main()
{
    setlocale(0, "");
   /* using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();*/

    srand(time(NULL));

    std::thread t1([]() {
        while (true)
        {
            run(new MyFramework);
        }
        });

    std::thread t2([]() {
        try
        {
            AsyncTCPClient client(4);
            tryConnection(client);
            client.close();
        }
        catch (system::system_error& e)
        {
            std::cout << "Error occured! Error code = " << e.code()
                << ". Message: " << e.what();

            std::cout << e.code().value() << std::endl;
            //return e.code().value();
        }
        });

    t1.join();
    t2.join();
   
    //auto t2 = high_resolution_clock::now();
    //duration<double, std::milli> ms_double = t2 - t1;
    //std::cout << ms_double.count() << "ms\n";
    return 0;
};