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

    // conduct error check for the image
    if (!texture.loadFromFile("images/tiles.jpg"))
    {
        std::cout << "Error loading image" << std::endl;
        return 1;
    }

    Sprite sprite(texture);
    const int tile_size = 32; // size of the tiles

    // create the board
    const int grid_size = 9;
    int running_grid[grid_size][grid_size] = {0};
    int answer_grid[grid_size][grid_size] = {0};

    // fill the board with bombs represented as 10
    int num_bombs = 10;
    while (num_bombs > 0)
    {
        int x = (std::rand() % 9);
        int y = (std::rand() % 9);

        if (x >= 0 && x < 9 && y >= 0 && y < 9)
        {
            if (answer_grid[x][y] != 10)
            {
                answer_grid[x][y] = 10;
                num_bombs -= 1;
            };
        }
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

    // prints the board
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << answer_grid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // game loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            // the window closes once we click on the close button
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        // draw the board
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (answer_grid[i][j] == 10)
                {
                    sprite.setTextureRect(IntRect(tile_size * 9, 0, tile_size, tile_size));
                }
                else
                {
                    sprite.setTextureRect(IntRect(tile_size * answer_grid[i][j], 0, tile_size, tile_size));
                }
                sprite.setPosition(j * tile_size, i * tile_size);
                window.draw(sprite);
            }
        }

        window.display(); // clear the window
    }

    // The program will end here when the window is closed
    return 0;
}
