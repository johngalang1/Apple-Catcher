#include "driver.h"

/* 
AUTHORS: John G, Zach L
FILE NAME: driver.c
PURPOSE: CONTAINS ALL FUNCTIONS FOR TESTING
*/

/*
NAME: test_display_message
PARAMETERS: None
PURPOSE: To display a "TIME UP" message at the top of the screen, centered horizontally.
DETAILS: Clears the screen, displays the message at specified coordinates, waits for any key press, then clears the message.
*/
void test_display_message()
{
    UINT32 *FB32 = Physbase();      
    message game_message;
    game_message.start_x = (SCREEN_WIDTH - (12 * 16)) / 2;  
    game_message.start_y = 20;   
    game_message.spacing = 16;   
    game_message.text = "TIME UP"; 
    clear_screen(FB32);  
    printf("Press Any Key to Clear Message\n");
    display_message(&game_message);
    Cnecin();
    clear_message(&game_message); 

    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");
}

/*
NAME: test_timer_decrement
PARAMETERS: None
PURPOSE: To decrement and display a round timer until it reaches 0.
DETAILS: Initializes the timer, clears the screen, displays the timer, 
        and decrements it upon each key press until it reaches zero.
*/

void test_timer_decrement() {
    UINT32 *FB32 = Physbase();
    UINT16 *FB16 = Physbase();
    timer_round *round_timer = init_round_timer();
    clear_screen(FB32); 
    printf("Press any key to decrement timer until it reaches 0\n");
    update_round_timer(FB16, round_timer);
    while(round_timer->value > 0)
    { 
        Cnecin();
        decrement_round_timer(FB16, round_timer);
    }

    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");
}

/*
NAME: test_basket_movement
PARAMETERS: None
PURPOSE: To test the movement of a basket object left and right across the screen.
DETAILS: Clears the screen, plots the basket at an initial position, moves it left and then right 
        by a set distance, and displays the updated position.
*/
void test_basket_movement()
{
    UINT32 *FB32 = Physbase();
    basket player_basket = {200, SCREEN_HEIGHT - 32, 8, 64, 16, basket_bitmap};  

    clear_screen(FB32); 
    
    /* Initial basket plot */
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    printf("Basket at:\n X = %d, Y = %d\n", player_basket.x, player_basket.y);

    /* Test moving the basket left */
    clear_basket(FB32, player_basket.x, player_basket.y, player_basket.width, player_basket.height);  
    player_basket.x -= player_basket.delta_x * 4; 
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);  
    printf("Basket moved left to:\n X = %d, Y = %d\n", player_basket.x, player_basket.y);

    /* Test moving the basket right */
    clear_basket(FB32, player_basket.x, player_basket.y, player_basket.width, player_basket.height); 
    player_basket.x += player_basket.delta_x * 4; 
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    printf("Basket moved right to:\n X = %d, Y = %d\n", player_basket.x, player_basket.y); 

    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");
}

/*
NAME: test_apple_collision
PARAMETERS: None
PURPOSE: To test if a falling apple collides with a basket positioned at the bottom of the screen.
DETAILS: Randomizes and sets the apple position above the basket, plots both objects, and checks for a collision, displaying the result.
*/
void test_apple_collision()
{
    UINT32 *FB32 = Physbase();
    apple falling_apple = {0, SCREEN_HEIGHT - 64, 32, 32};  
    basket player_basket = {200, SCREEN_HEIGHT - 32, 8, 64, 16, basket_bitmap};  
    srand(time(NULL));

    clear_screen(FB32);
    /* Randomize apple position on the same horizontal axis as the basket */
    reset_apple_position(&falling_apple);

    /* Set apple directly above the basket */
    falling_apple.y = player_basket.y - falling_apple.height;

    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    plot_apple_32(FB32, falling_apple.x, falling_apple.y, apple_bitmap, falling_apple.height);

    if (check_apple_collision(&player_basket, &falling_apple))
    {
        printf("Apple collided with the basket! Position: X = %d, Y = %d\n", falling_apple.x, falling_apple.y);
    }
    else
    {
        printf("No collision detected. Apple Position: X = %d, Y = %d\n", falling_apple.x, falling_apple.y);
    }
    printf("Press 2 to try again\n");
    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");
}

/*
NAME: test_random_apple_position
PARAMETERS: None
PURPOSE: To set a random position for an apple and display it on the screen.
DETAILS: Randomizes the apple's position, plots it above the screen, and prints its coordinates.
*/
void test_random_apple_position()
{
    UINT32 *FB32 = Physbase();
    /* Apple starting above the screen */
    apple falling_apple = {200, -32, 32, 32}; 
    /* Randomize apple position */
    reset_apple_position(&falling_apple); 
    plot_apple_32(FB32, falling_apple.x, falling_apple.y, apple_bitmap, falling_apple.height);
    
    printf("New random apple position: X = %d, Y = %d\n", falling_apple.x, falling_apple.y);

    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");
} 

/*
NAME: test_basket_right_border_collision
PARAMETERS: None
PURPOSE: To test if the basket collides with the right screen border when moving right.
DETAILS: Plots the right border line, moves the basket right until it reaches the border, 
        and stops upon collision.
*/
void test_basket_right_border_collision()
{
    UINT32 *FB32 = Physbase();
    UINT16 *FB16 = (UINT16*) Physbase();  
    basket player_basket = {320, 300, 8, 64, 16, basket_bitmap};  
    int direction = 1;  
    
    clear_screen(FB32);
    plot_vertical_line(FB16, RIGHT_BORDER, 0, SCREEN_HEIGHT);  
    printf("Testing Basket Collision with Right Border\n");
    
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    printf("Initial Basket Position: X = %d, Y = %d\n", player_basket.x, player_basket.y);
    
    /* Move the basket right and check for right border collision */
    while (player_basket.x < RIGHT_BORDER - player_basket.width)  
    {
        clear_basket(FB32, player_basket.x, player_basket.y, player_basket.width, player_basket.height);  

        /* Move basket to the right */
        player_basket.x += direction * player_basket.delta_x;
        plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
        check_basket_collision(&player_basket);
        
        if (player_basket.x == RIGHT_BORDER - player_basket.width)
        {
            printf("Basket collided with RIGHT border at X = %d\n", player_basket.x);
            break; 
        }
    }
    printf("Final Basket Position: X = %d, Y = %d\n", player_basket.x, player_basket.y);
    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");
}


/*
NAME: test_basket_left_border_collision
PARAMETERS: None
PURPOSE: To test if the basket collides with the left screen border when moving left.
DETAILS: Plots the left border line, moves the basket left until it reaches the border, 
        and stops upon collision.
*/
void test_basket_left_border_collision()
{
    UINT32 *FB32 = Physbase();
    UINT16 *FB16 = (UINT16*) Physbase();  
    basket player_basket = {320, 300, 8, 64, 16, basket_bitmap};  
    int direction = -1;  
    
    clear_screen(FB32);
    plot_vertical_line(FB16, LEFT_BORDER, 0, SCREEN_HEIGHT);  
    printf("Testing Basket Collision with Left Border\n");
    /* Plot initial basket position */
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    printf("Initial Basket Position: X = %d, Y = %d\n", player_basket.x, player_basket.y);
    
    /* Move the basket left and check for left border collision */
    while (player_basket.x > LEFT_BORDER)  
    {
        clear_basket(FB32, player_basket.x, player_basket.y, player_basket.width, player_basket.height);  

        /* Move basket to the left */
        player_basket.x += direction * player_basket.delta_x;
        plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
        check_basket_collision(&player_basket);
        
        if (player_basket.x == LEFT_BORDER + 32)
        {
            check_basket_collision(&player_basket);
            printf("Basket collided with LEFT border at X = %d\n", player_basket.x);
            break;
        }
    }
    printf("Final Basket Position: X = %d, Y = %d\n", player_basket.x, player_basket.y);
    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");
}

/*
NAME: test_apple_movement
PARAMETERS: None
PURPOSE: To test the movement of an apple from the top of the screen to the bottom.
DETAILS: Clears the screen, randomizes the apple's starting position at the top, moves downward by 2 pixels 
        until it reaches the bottom, and then resets its position.
*/
void test_apple_movement()
{
    UINT32 *FB32 = Physbase();
    apple falling_apple = {0, 0, 32, 32}; 

    clear_screen(FB32);
    /* Randomize the apple position at the top */
    reset_apple_position(&falling_apple);

    plot_apple_32(FB32, falling_apple.x, falling_apple.y, apple_bitmap, APPLE_HEIGHT);
    printf("Apple spawned at: X = %d, Y = %d (Top)\n", falling_apple.x, falling_apple.y);

    while(falling_apple.y <= SCREEN_HEIGHT)
    { 
       move_apple(FB32, &falling_apple);
    }

    printf("Apple moved to: X = %d, Y = %d\n", falling_apple.x, falling_apple.y);

    reset_apple_position(&falling_apple);
    
    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");

}

/*
NAME: test_score_increment
PARAMETERS: None
PURPOSE: To test incrementing and displaying the game score up to a maximum value of 99.
DETAILS: Clears the screen, displays the initial score, and increments it with each key press until reaching 99, updating the display each time.
*/

void test_score_increment()
{
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = (UINT16*) Physbase();  
    score *game_score = init_score();  
    clear_screen(FB32);  
    printf("Press any key to increment score up to 99\n");
    printf("Initial score: %d\n", game_score->value);
    update_score(FB16, game_score);

    while (game_score->value != 99)
    {
        increment_score(FB16, game_score);
        update_score(FB16, game_score);
        Cnecin(); 
    }
    
printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");

}
