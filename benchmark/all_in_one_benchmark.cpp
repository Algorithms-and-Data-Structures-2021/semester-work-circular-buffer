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

const int kMinSamples = 100;
const int kMaxSamples = 5000000;


int main(int argc, char **argv) {

  // работа с набором данных
  const auto path = string(kDatasetPath);
  cout << "Path to the 'dataset/' folder: " << path << endl;


  for (int file_index = kMinSamples; file_index <= kMaxSamples; file_index = (to_string(file_index)[0] == '1') ? file_index*5 : file_index*2) {
    string file = to_string(file_index) + ".csv";

    for (int folder_idx = 1; folder_idx < 11; folder_idx++){
      string folder;
      if (folder_idx < 10)  {
        folder = '0' + to_string(folder_idx);
      } else {
        folder = to_string(folder_idx);
      }

      cout << '.';
    }
  }


  // Tip 1: входные аргументы позволяют более гибко контролировать параметры вашей программы

  // Можете передать путь до входного/выходного файла в качестве аргумента,
  // т.е. не обязательно использовать kDatasetPath и прочие константы

  for (int index = 0; index < argc; index++) {
    cout << "Arg: " << argv[index] << '\n';
  }

  // Tip 2: для перевода строки в число можете использовать функцию stoi (string to integer)

  // можете использовать функционал класса stringstream для обработки строки
  auto ss = stringstream("0 1 2");  // передаете строку (входной аргумент или строку из файла) и обрабатываете ее

  int number = 0;
  ss >> number;  // number = 0
  ss >> number;  // number = 1
  ss >> number;  // number = 2


  auto input_file = ifstream(path + "/dataset-example.csv");

  if (input_file) {
    // чтение и обработка набора данных ...
  }

  // Контрольный тест: операции добавления, удаления, поиска и пр. над структурой данных

  // Tip 3: время работы программы (или участка кода) можно осуществить
  // как изнутри программы (std::chrono), так и сторонними утилитами

  const auto time_point_before = chrono::high_resolution_clock::now();

  // здесь находится участок кода, время которого необходимо замерить

  const auto time_point_after = chrono::high_resolution_clock::now();

  // переводим время в наносекунды
  const auto time_diff = time_point_after - time_point_before;
  const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();

  cout << "Time elapsed (ns): " << time_elapsed_ns << '\n';

  return 0;
}