/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiyang <tiyang@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/24 11:46:59 by tiyang        #+#    #+#                 */
/*   Updated: 2025/11/26 13:01:35 by tiyang        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Define some colors for testing
#define COLOR_CEILING 0x87CEEB // Sky Blue
#define COLOR_FLOOR   0x8B4513 // Saddle Brown
#define COLOR_WALL_1  0xFF0000 // Red (Side 0)
#define COLOR_WALL_2  0x00FF00 // Green (Side 1)

// Define generic texture width for calculation (usually 64)
#define TEX_WIDTH 64

// Fast pixel put (replaces mlx_pixel_put)
void    my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = game->img.addr + (y * game->img.line_length + x * (game->img.bpp / 8));
    *(unsigned int *)dst = color;
}

unsigned int	get_texture_pixel(t_img *tex, int x, int y)
{
	char	*dst;

	if (!tex->addr)
		return (0xFFFFFF); // fallback color (white)
	dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

// Draw a vertical line of pixels
// void    draw_vertical_line(t_game *game, int x, int drawStart, int drawEnd, int color)
// {
//     int y;

//     // 1. Draw Ceiling (From 0 to drawStart)
//     y = 0;
//     while (y < drawStart)
//     {
//         my_mlx_pixel_put(game, x, y, COLOR_CEILING);
//         y++;
//     }

//     // 2. Draw Wall (From drawStart to drawEnd)
//     y = drawStart;
//     while (y < drawEnd)
//     {
//         my_mlx_pixel_put(game, x, y, color);
//         y++;
//     }

//     // 3. Draw Floor (From drawEnd to HEIGHT)
//     y = drawEnd;
//     while (y < HEIGHT)
//     {
//         my_mlx_pixel_put(game, x, y, COLOR_FLOOR);
//         y++;
//     }
// }
// -----------------------------------------------------------------------------
// NEW: Fill the entire screen with ceiling/floor colors at once
// -----------------------------------------------------------------------------
void	render_background(t_game *game)
{
	unsigned int	*dst;
	int				i;
	int				total_pixels;

	// We treat the image buffer as a big array of unsigned ints (colors)
	dst = (unsigned int *)game->img.addr;
	total_pixels = WIDTH * HEIGHT;
	
	// Fill first half with Ceiling Color
	i = 0;
	while (i < total_pixels / 2)
	{
		dst[i] = game->ceiling_color;
		i++;
	}

	// Fill second half with Floor Color
	while (i < total_pixels)
	{
		dst[i] = game->floor_color;
		i++;
	}
}

void	draw_vertical_line(t_game *game, int x, int drawStart, int drawEnd,
			t_img *tex, int texX)
{
	int y;
	int texY;
	int color;
	int lineHeight = drawEnd - drawStart;
	int	d; // variable for texture calculation

	// Draw ceiling
	// y = 0;
	// while (y < drawStart)
	// {
	// 	my_mlx_pixel_put(game, x, y, game->ceiling_color);
	// 	y++;
	// }

	// ============== OLD DRAW WALL LOOP =================
	// // Draw wall with texture
	// y = drawStart;
	// while (y < drawEnd)
	// {
	// 	texY = (int)(((y - drawStart) * tex->height) / lineHeight);
	// 	if (texY < 0)
	// 		texY = 0;
	// 	if (texY >= tex->height)
	// 		texY = tex->height - 1;
	// 	color = get_texture_pixel(tex, texX, texY);
	// 	my_mlx_pixel_put(game, x, y, color);
	// 	y++;
	// }

	// ============== NEW DRAW WALL LOOP =================
	y = drawStart;
	while (y < drawEnd)
	{
		// Calculate texY. This method handles "clamped" walls correctly
		// so textures don't squash when you get close.
		d = y * 256 - HEIGHT * 128 + lineHeight * 128;
		texY = ((d * tex->height) / lineHeight) / 256;
		
		// Safety check for texture coordinates
		if (texY < 0) texY = 0;
		if (texY >= tex->height) texY = tex->height - 1;

		color = get_texture_pixel(tex, texX, texY);
		
		// Only draw if color is not completely transparent (optional)
		if ((color & 0xFF000000) == 0)
			my_mlx_pixel_put(game, x, y, color);
		y++;
	}

	
	// // Draw floor
	// y = drawEnd;
	// while (y < HEIGHT)
	// {
	// 	my_mlx_pixel_put(game, x, y, game->floor_color);
	// 	y++;
	// }
}

void raycast(t_game *game)
{
    int x;

	render_background(game);
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
            if (game->map[mapY][mapX] == '1') 
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

        // // DEBUG: Print distance for the middle ray only
        // if (x == WIDTH / 2)
        // {
        //     printf("Mid Ray Hit at Map[%d][%d]. Distance: %f\n", 
        //            mapX, mapY, perpWallDist);
        // }
		// Calculate height of line to draw on screen
        int lineHeight = (int)(HEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if (drawEnd >= HEIGHT)
            drawEnd = HEIGHT - 1;

		// ---------------------------------------------------------
        // PART 4b: Calculate Texture Coordinates (NEW CODE)
        // ---------------------------------------------------------
        
        double wallX; // Precise position of where the wall was hit

        // 1. Calculate value of wallX
        if (side == 0)
             wallX = game->posY + perpWallDist * rayDirY;
        else
             wallX = game->posX + perpWallDist * rayDirX;

        // 2. Normalize wallX to be between 0 and 1 (fractional part)
        wallX -= floor(wallX);

        // 3. x coordinate on the texture
        // int texX = (int)(wallX * (double)TEX_WIDTH);

        // 4. Flip texture if we are looking at specific sides to avoid mirroring
        // if (side == 0 && rayDirX > 0)
        //     texX = TEX_WIDTH - texX - 1;
        // if (side == 1 && rayDirY < 0)
        //     texX = TEX_WIDTH - texX - 1;
		t_img *texture;

		// Choose the texture based on wall side
		if (side == 0) // EW walls
		{
			if (rayDirX > 0)
				texture = &game->tex_we;
			else
				texture = &game->tex_ea;
		}
		else // NS walls
		{
			if (rayDirY > 0)
				texture = &game->tex_no;
			else
				texture = &game->tex_so;
		}

		// Use the actual width of the chosen texture
		int texX = (int)(wallX * (double)texture->width);

		
		// ============ ADJUSTED TEXTURE CALCULATION LOGIC ===============
		if (side == 0 && rayDirX > 0) texX = texture->width - texX - 1;
        if (side == 1 && rayDirY < 0) texX = texture->width - texX - 1;

		// ============ OLD TEXTURE CALCULATION LOGIC AS SAFETY CHECK ===============
		if (texX < 0)
			texX = 0;
		if (texX >= texture->width)
			texX = texture->width - 1;

        // DEBUG: Uncomment to verify texX is changing between 0 and 63
        // if (x == WIDTH / 2)
        //     printf("Mid Ray: WallX: %f | TexX: %d\n", wallX, texX);

        // ---------------------------------------------------------
        // PART 5: Set Color & Draw
        // ---------------------------------------------------------
		
        // int color;
        // // Give x-side and y-side different brightness/color for depth
        // if (side == 0)
        //     color = COLOR_WALL_1;
        // else
        //     color = COLOR_WALL_2;

        // draw_vertical_line(game, x, drawStart, drawEnd, color);

		// t_img *texture;


		draw_vertical_line(game, x, drawStart, drawEnd, texture, texX);

        x++;
    }
    // Note: We aren't drawing anything yet, just running the math loop!
	// ---------------------------------------------------------
    // PART 5: Push to Window (Day 4)
    // ---------------------------------------------------------
    // We draw the entire buffer to the window at once
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
}

