#include <sort.hpp>
#include <catch.hpp>
#include <string>
#include <iostream>
#include <fstream>

// SCENARIO("8mb", "[8mb]")
// {
//   REQUIRE(1 == 1);
// }

SCENARIO("8mb", "[8mb]")
{
  setlocale(LC_ALL, "Russian");
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  sorting("8mb","8out_8",1);
  end = std::chrono::system_clock::now();
  int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
  (end - start).count();
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds << "s\n";
  bool x = true;
  std::ifstream f1("out_8"), f2("out8");
  line s1, s2;
  while(!f2.eof() && !f1.eof())
  {
    if((f1>>s1)&&(f2>>s2))
    {
      if(s1.name!=s2.name)
      {
        x=false;
        break;
      }
    }
    else break;
  }
  f1.close();
  f2.close();
  REQUIRE(x);
}

SCENARIO("15mb", "[15mb]")
{
  setlocale(LC_ALL, "Russian");
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  sorting("15mb", "out_15", 4);
  end = std::chrono::system_clock::now();
  int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
  (end - start).count();
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds << "s\n";
  bool x = true;
  std::ifstream f1("out_15"), f2("out15");
  line s1, s2;
  while(!f2.eof() && !f1.eof())
  {
    if((f1>>s1)&&(f2>>s2))
    {
      if(s1.name!=s2.name)
      {
        x=false;
        break;
      }
    }
    else break;
  }
  f1.close();
  f2.close();
  REQUIRE(x);
}

SCENARIO("32mb", "[32mb]")
{
  setlocale(LC_ALL, "Russian");
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  sorting("32mb", "out_32", 17);
  end = std::chrono::system_clock::now();
  int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
  (end - start).count();
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);
  std::cout << "finished computation at " << std::ctime(&end_time) << "elapsed time: " << elapsed_seconds << "s\n";
  bool x = true;
  std::ifstream f1("out_32"), f2("out32");
  line s1, s2;
  while(!f2.eof() && !f1.eof())
  {
    if((f1>>s1)&&(f2>>s2))
    {
      if(s1.name!=s2.name)
      {
        x=false;
        break;
      }
    }
    else break;
  }
  f1.close();
  f2.close();
  REQUIRE(x);
}
