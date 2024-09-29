#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <Rectangle.hpp>
#include <json.hpp>

using json = nlohmann::json;

auto parseRectangle(const uint id, const json& json_rect) -> rectangle
{
  const auto rect = rectangle {
      id, json_rect["h"], json_rect["w"], json_rect["x"], json_rect["y"]};
  rect.print();
  return rect;
}

auto main(int argc, const char** argv) -> int
{
  if (argc < 2) {
    std::cerr << "Please specify the file that shall be read" << std::endl;
    return 1;
  }
  std::vector<rectangle> rectangles;
  uint rect_counter = 1;

  try {
    const std::filesystem::path filename {argv[1]};
    if (!std::filesystem::exists(filename)) {
      std::cerr << "File " << filename << " does not exist" << std::endl;
      return 2;
    }
    std::ifstream test_file(filename);
    json data = json::parse(test_file);
    std::cout << "Input:" << std::endl;
    for (const auto& json_rectangle : data["rects"]) {
      const auto rect = parseRectangle(rect_counter++, json_rectangle);
      rectangles.emplace_back(rect);
      if (rect_counter > 10) {
        std::cout
            << "Only the first 10 rectangles will be considered. If you "
               "require more create a JIRA ticket to request a new feature"
            << std::endl;
        break;
      }
    }
  } catch (const std::exception& e) {
    std::cerr << "Invalid input file provided. Please use a valid input file"
              << std::endl;
    std::cerr << e.what();
    return 1;
  }
  std::cout << std::endl << "Intersections" << std::endl;

  intersectRectangles(rectangles);
  return 0;
}
