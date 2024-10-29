#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <tuple>
#include <cstdlib>

using namespace sf;

int main()
{
    // create the interface
    RenderWindow window(VideoMode(400, 400), "MineSweeper");
    Texture texture;
    texture.loadFromFile("images/tiles.jpg");
    Sprite sprite(texture);

    // create the board
    const int gridSize = 9;
    int width = 10;
    int running_grid[gridSize][gridSize] = {0};
    int answer_grid[gridSize][gridSize] = {0};

    // fill the board with bombs represented as 10
    int num_bombs = 10;
    while (num_bombs > 0)
    {
        int x = rand() % gridSize;
        int y = rand() % gridSize;

        if (answer_grid[x][y] != 10)
        {
            answer_grid[x][y] = 10;
            num_bombs -= 1;
        };
    }

    // fill the rest of the board with the numbers of bombs
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (answer_grid[i][j] != 10)
            {
                int count = 0;
                std::tuple<int, int> coord[8] = {
                    std::make_tuple(i - 1, j - 1),
                    std::make_tuple(i - 1, j),
                    std::make_tuple(i - 1, j + 1),
                    std::make_tuple(i, j - 1),
                    std::make_tuple(i, j + 1),
                    std::make_tuple(i + 1, j - 1),
                    std::make_tuple(i + 1, j),
                    std::make_tuple(i + 1, j + 1),
                };

                for (int k = 0; k < 8; k++)
                {
                    int x = std::get<0>(coord[k]);
                    int y = std::get<1>(coord[k]);

                    if (x >= 0 && x < 9 && y >= 0 && y < 9)
                    {
                        if (answer_grid[x][y] == 10)
                        {
                            count += 1;
                        }
                    }
                };

                answer_grid[i][j] = count;
            }
        }
    }

    // Run the program
    while (window.isOpen())
    {
        // Process events
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close(); // Close the window if the close event is triggered
            }
        }

        // Clear the window
        window.clear();

        // Draw the grid
        float cellSize = 400.0f / gridSize; // Calculate cell size
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                RectangleShape cell(Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);
                cell.setOutlineColor(Color::Black);
                cell.setOutlineThickness(1.0f); // Optional: add a border to the cells

                // Set the fill color based on the cell value
                if (answer_grid[i][j] == 10) // If there's a bomb
                {
                    cell.setFillColor(Color::Red); // Bomb cells can be red
                }
                else
                {
                    cell.setFillColor(Color::White); // Non-bomb cells can be white
                }

                window.draw(cell); // Draw the cell
            }
        }

        // Display what has been drawn
        window.display();
    }

    // The program will end here when the window is closed
    return 0;
    // end the program
}
