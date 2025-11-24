/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/24 11:46:59 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/24 14:12:11 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void raycast(t_game *game)
{
    int x;

    x = 0;
    // LOOP: Iterate through every vertical column of the screen
    while (x < WIDTH)
    {
        // ---------------------------------------------------------
        // PART 1: Calculate Ray Position and Direction
        // ---------------------------------------------------------
        
        // cameraX: x-coordinate in camera space
        // Ranges from -1 (left side of screen) to 1 (right side)
        double cameraX = 2 * x / (double)WIDTH - 1; 

        // Ray direction vector = Direction vector + Plane vector * cameraX
        double rayDirX = game->dirX + game->planeX * cameraX;
        double rayDirY = game->dirY + game->planeY * cameraX;

        // // ---------------------------------------------------------
        // // DEBUGGING 
        // // Print the first ray's data to verify math is working
        // // ---------------------------------------------------------
        // if (x == WIDTH / 2) // Middle of the screen
        // {
        //     printf("Mid Ray: DirX: %f, DirY: %f, MapVal: %d\n", 
        //         rayDirX, rayDirY, 
        //         game->test_map[(int)game->posY][(int)game->posX]);
        // }
		// ---------------------------------------------------------
        // PART 2: DDA Setup 
        // ---------------------------------------------------------
        
        // Map coordinates: Which box of the map we're in
        int mapX = (int)game->posX;
        int mapY = (int)game->posY;

        // Length of ray from one x or y-side to next x or y-side
        // Formula: deltaDistX = abs(1 / rayDirX)
        // We use a large number (1e30) if rayDir is 0 to avoid division by zero
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double sideDistX; // Length of ray from current position to next x-side
        double sideDistY; // Length of ray from current position to next y-side
        
        int stepX; // Direction to step in x-axis (+1 or -1)
        int stepY; // Direction to step in y-axis (+1 or -1)

        int hit = 0; // Was there a wall hit?
        int side;    // Was a NS or a EW wall hit? (0 for X-wall, 1 for Y-wall)

        // Calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
        }

        // ---------------------------------------------------------
        // PART 3: DDA Loop 
        // ---------------------------------------------------------
        // Perform DDA
        while (hit == 0)
        {
            // Jump to next map square, either in x-direction, or in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; // Hit an X-side wall (East/West)
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; // Hit a Y-side wall (North/South)
            }

            // Check if ray has hit a wall
            // Note: We use the hardcoded test_map for now
            if (game->test_map[mapY][mapX] > 0) 
                hit = 1;
        }

        // ---------------------------------------------------------
        // PART 4: Calculate Distance 
        // ---------------------------------------------------------
        // Calculate distance projected on camera direction (Perpendicular distance)
        // This prevents the "fisheye" effect.
        double perpWallDist;
        if (side == 0) 
            perpWallDist = (sideDistX - deltaDistX);
        else           
            perpWallDist = (sideDistY - deltaDistY);

        // DEBUG: Print distance for the middle ray only
        if (x == WIDTH / 2)
        {
            printf("Mid Ray Hit at Map[%d][%d]. Distance: %f\n", 
                   mapX, mapY, perpWallDist);
        }

        x++;
    }
    // Note: We aren't drawing anything yet, just running the math loop!
}

