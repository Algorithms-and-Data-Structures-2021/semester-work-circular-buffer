#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds
#include <sstream>      // stringstream

// подключаем вашу структуру данных
#include "circular_buffer.hpp"

using namespace std;
using namespace itis;

// абсолютный путь до набора данных и папки проекта
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};
static constexpr auto kProjectPath = string_view{PROJECT_SOURCE_DIR};

const string kEnqueueDatasetPath = "/Enqueue/int/02";

const int kMinSamples = 100;
const int kMaxSamples = 5000000;

const int kBigBufferCoeff = 5;
const int kSmallBufferCoeff = 2;


long test_enqueue_back(string path_to_input_file, itis::circular_buffer<int> buff) {
  string line;
  auto input_file = ifstream(path_to_input_file);
  auto time_point_before = chrono::high_resolution_clock::now();
  while (getline(input_file, line)) {
    int number = stoi(line);
    buff.EnqueueBack(number);
  }
  auto time_point_after = chrono::high_resolution_clock::now();
  auto time_diff = time_point_after - time_point_before;
  long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();

  return time_elapsed_ns;
}


long test_enqueue_front(string path_to_input_file, itis::circular_buffer<int> buff) {
  string line;
  auto input_file = ifstream(path_to_input_file);
  auto time_point_before = chrono::high_resolution_clock::now();
  while (getline(input_file, line)) {
    int number = stoi(line);
    buff.EnqueueFront(number);
  }
  auto time_point_after = chrono::high_resolution_clock::now();
  auto time_diff = time_point_after - time_point_before;
  long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();

  return time_elapsed_ns;
}


long test_dequeue_back(itis::circular_buffer<int> buff) {
  auto time_point_before = chrono::high_resolution_clock::now();
  while (!buff.isEmpty()) {
    buff.DequeueBack();
  }
  auto time_point_after = chrono::high_resolution_clock::now();
  auto time_diff = time_point_after - time_point_before;
  long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();

  return time_elapsed_ns;
}


long test_dequeue_front(itis::circular_buffer<int> buff) {
  auto time_point_before = chrono::high_resolution_clock::now();
  while (!buff.isEmpty()) {
    buff.DequeueFront();
  }
  auto time_point_after = chrono::high_resolution_clock::now();
  auto time_diff = time_point_after - time_point_before;
  long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();

  return time_elapsed_ns;
}


int main(int argc, char **argv) {

  // работа с набором данных
  const auto path = string(kDatasetPath);
  cout << "Path to the 'dataset/' folder: " << path << endl;


  for (int samples_num = kMinSamples; samples_num <= kMaxSamples;
       samples_num = (to_string(samples_num)[0] == '1') ? samples_num *5 : samples_num *2) {
    string file = "/" + to_string(samples_num) + ".csv";

    for (int folder_idx = 1; folder_idx < 11; folder_idx++){
      string folder;
      if (folder_idx < 10)  {
        folder = '0' + to_string(folder_idx);
      } else {
        folder = to_string(folder_idx);
      }

      string path_to_file = path + kEnqueueDatasetPath + folder + file;
      auto buff = itis::circular_buffer<int>(samples_num / kSmallBufferCoeff);

      long time_elapsed_ns_enqueue_back_small = test_enqueue_back(path_to_file, buff);
      long time_elapsed_ns_dequeue_back_small = test_dequeue_back(buff);
      long time_elapsed_ns_enqueue_front_small = test_enqueue_front(path_to_file, buff);
      long time_elapsed_ns_dequeue_front_small = test_dequeue_front(buff);

      buff.Resize(samples_num + kBigBufferCoeff);

      long time_elapsed_ns_enqueue_back_big = test_enqueue_back(path_to_file, buff);
      long time_elapsed_ns_dequeue_back_big = test_dequeue_back(buff);
      long time_elapsed_ns_enqueue_front_big = test_enqueue_front(path_to_file, buff);
      long time_elapsed_ns_dequeue_front_big = test_dequeue_front(buff);

      cout << time_elapsed_ns_enqueue_back_small << "        " << time_elapsed_ns_enqueue_back_big << endl;
      cout << time_elapsed_ns_enqueue_front_small << "        " << time_elapsed_ns_enqueue_front_big << endl;
      cout << time_elapsed_ns_dequeue_back_small << "        " << time_elapsed_ns_dequeue_back_big << endl;
      cout << time_elapsed_ns_dequeue_front_small << "        " << time_elapsed_ns_dequeue_front_big << endl;

    }
  }
//
//  string input_file_ = path + "/Enqueue/int/02/" + "100.csv";
//  auto buff_ = itis::circular_buffer<int>(50);
//  test_enqueue_back(input_file_, buff_);


  // Tip 1: входные аргументы позволяют более гибко контролировать параметры вашей программы

  // Можете передать путь до входного/выходного файла в качестве аргумента,
  // т.е. не обязательно использовать kDatasetPath и прочие константы
//
//  for (int index = 0; index < argc; index++) {
//    cout << "Arg: " << argv[index] << '\n';
//  }
//
//  // Tip 2: для перевода строки в число можете использовать функцию stoi (string to integer)
//
//  // можете использовать функционал класса stringstream для обработки строки
//  auto ss = stringstream("0 1 2");  // передаете строку (входной аргумент или строку из файла) и обрабатываете ее
//
//  int number = 0;
//  ss >> number;  // number = 0
//  ss >> number;  // number = 1
//  ss >> number;  // number = 2

//
//  auto input_file = ifstream(path + "/dataset-example.csv");
//
//  if (input_file) {
//    // чтение и обработка набора данных ...
//  }

  // Контрольный тест: операции добавления, удаления, поиска и пр. над структурой данных

  // Tip 3: время работы программы (или участка кода) можно осуществить
  // как изнутри программы (std::chrono), так и сторонними утилитами

//  const auto time_point_before = chrono::high_resolution_clock::now();

  // здесь находится участок кода, время которого необходимо замерить

//  const auto time_point_after = chrono::high_resolution_clock::now();

  // переводим время в наносекунды
//  const auto time_diff = time_point_after - time_point_before;
//  const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();

//  cout << "Time elapsed (ns): " << time_elapsed_ns << '\n';

  return 0;
}
