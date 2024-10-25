#include "driver.h"


void test_display_message()
{
    UINT32 *FB32 = Physbase();      
    /* Define the message to display */
    message game_message;
    game_message.start_x = (SCREEN_WIDTH - (12 * 16)) / 2;  /* Center the message horizontally */
    game_message.start_y = 20;   /* Vertical position at the top of the screen */
    game_message.spacing = 16;   /* Spacing between letters */
    game_message.text = "TIME UP"; /* The message text */
    clear_screen(FB32);  
    printf("Press Any Key to Clear Message\n");
    /* Display the message */
    display_message(&game_message);
    /* Simulate waiting for user input before clearing the message */
    Cnecin();
    /* Clear the message from the screen */
    clear_message(&game_message); 

    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");


}

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

/* Test basket movement by moving it left and right */
void test_basket_movement()
{
    UINT32 *FB32 = Physbase();
    basket player_basket = {200, SCREEN_HEIGHT - 32, 8, 64, 16, basket_bitmap};  /* Basket near the bottom */

    clear_screen(FB32);  /* Clear the screen initially */
    
    /* Initial basket plot */
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    printf("Basket at:\n X = %d, Y = %d\n", player_basket.x, player_basket.y);

    /* Test moving the basket left */
    clear_basket(FB32, player_basket.x, player_basket.y, player_basket.width, player_basket.height);  /* Clear the old position */
    player_basket.x -= player_basket.delta_x * 4;  /* Move left */
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);  /* Plot new position */
    printf("Basket moved left to:\n X = %d, Y = %d\n", player_basket.x, player_basket.y);

    /* Test moving the basket right */
    clear_basket(FB32, player_basket.x, player_basket.y, player_basket.width, player_basket.height);  /* Clear the old position */
    player_basket.x += player_basket.delta_x * 4;  /* Move right by twice the step */
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);  /* Plot new position */
    printf("Basket moved right to:\n X = %d, Y = %d\n", player_basket.x, player_basket.y); 

    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");


}


/* Test apple collision with basket without movement or animation */
void test_apple_collision()
{
    UINT32 *FB32 = Physbase();
    apple falling_apple = {0, SCREEN_HEIGHT - 64, 32, 32};  /* Apple on the same horizontal axis as the basket */
    basket player_basket = {200, SCREEN_HEIGHT - 32, 8, 64, 16, basket_bitmap};  /* Basket near the bottom */
    srand(time(NULL));

    clear_screen(FB32);

    /* Randomize apple position on the same horizontal axis as the basket */
    reset_apple_position(&falling_apple);

    /* Set apple directly above the basket */
    falling_apple.y = player_basket.y - falling_apple.height;

    /* Plot the basket and the apple */
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    plot_apple_32(FB32, falling_apple.x, falling_apple.y, apple_bitmap, falling_apple.height);

    /* Check for collision */
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



/* Test random apple position generation */
void test_random_apple_position()
{
    UINT32 *FB32 = Physbase();
    apple falling_apple = {200, -32, 32, 32};  /* Apple starting above the screen */
    
    reset_apple_position(&falling_apple);  /* Randomize apple position */
    plot_apple_32(FB32, falling_apple.x, falling_apple.y, apple_bitmap, falling_apple.height);
    
    /* Print the new apple position */
    printf("New random apple position: X = %d, Y = %d\n", falling_apple.x, falling_apple.y);

    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");


} 

/* Test basket collision with the right border using check_basket_collision */
void test_basket_right_border_collision()
{
    UINT32 *FB32 = Physbase();
    UINT16 *FB16 = (UINT16*) Physbase();  
    basket player_basket = {320, 300, 8, 64, 16, basket_bitmap};  /* Basket starting position */
    int direction = 1;  /* Start by moving to the right */
    
    clear_screen(FB32);
    plot_vertical_line(FB16, RIGHT_BORDER, 0, SCREEN_HEIGHT);  /* Right border */
    printf("Testing Basket Collision with Right Border\n");
    
    /* Plot initial basket position */
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    printf("Initial Basket Position: X = %d, Y = %d\n", player_basket.x, player_basket.y);
    
    /* Move the basket right and check for right border collision */
    while (player_basket.x < RIGHT_BORDER - player_basket.width)  /* Keep moving until collision */
    {
        clear_basket(FB32, player_basket.x, player_basket.y, player_basket.width, player_basket.height);  /* Clear old position */

        /* Move basket to the right */
        player_basket.x += direction * player_basket.delta_x;

        /* Call the collision check function */
        check_basket_collision(&player_basket);
        
        /* Break if collision happens */
        if (player_basket.x == RIGHT_BORDER - player_basket.width)
        {
            printf("Basket collided with RIGHT border at X = %d\n", player_basket.x);
            break;  /* Stop after colliding */
        }

    }
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    printf("Final Basket Position: X = %d, Y = %d\n", player_basket.x, player_basket.y);
    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");


}


/* Test basket collision with the left border using check_basket_collision */
void test_basket_left_border_collision()
{
    UINT32 *FB32 = Physbase();
    UINT16 *FB16 = (UINT16*) Physbase();  
    basket player_basket = {320, 300, 8, 64, 16, basket_bitmap};  /* Basket starting position */
    int direction = -1;  /* Start by moving to the left */
    
    clear_screen(FB32);
    plot_vertical_line(FB16, LEFT_BORDER, 0, SCREEN_HEIGHT);  /* Left border */
    printf("Testing Basket Collision with Left Border\n");
    /* Plot initial basket position */
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    printf("Initial Basket Position: X = %d, Y = %d\n", player_basket.x, player_basket.y);
    
    /* Move the basket left and check for left border collision */
    while (player_basket.x > LEFT_BORDER)  /* Keep moving until collision */
    {
        clear_basket(FB32, player_basket.x, player_basket.y, player_basket.width, player_basket.height);  /* Clear old position */

        /* Move basket to the left */
        player_basket.x += direction * player_basket.delta_x;

        /* Call the collision check function */
        check_basket_collision(&player_basket);
        
        /* Break if collision happens */
        if (player_basket.x == LEFT_BORDER + 32)
        {
            printf("Basket collided with LEFT border at X = %d\n", player_basket.x);
            break;  /* Stop after colliding */
        }

    }
    plot_basket_64(FB32, player_basket.x, player_basket.y, player_basket.bitmap, player_basket.height);
    printf("Final Basket Position: X = %d, Y = %d\n", player_basket.x, player_basket.y);
    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");


}

/* Test apple movement from the top to the bottom using the move_apple function */
void test_apple_movement()
{
    UINT32 *FB32 = Physbase();
    apple falling_apple = {0, 0, 32, 32};  /* Apple starts above the screen */

    /* Clear screen initially */
    clear_screen(FB32);
    
    /* Randomize the apple position at the top */
    reset_apple_position(&falling_apple);

    /* Plot the apple at the random starting position at the top */
    plot_apple_32(FB32, falling_apple.x, falling_apple.y, apple_bitmap, APPLE_HEIGHT);
    printf("Apple spawned at: X = %d, Y = %d (Top)\n", falling_apple.x, falling_apple.y);

    /* Move the apple using the move_apple function */
    move_apple(FB32, &falling_apple);

    /* Print the new position of the apple after moving */
    printf("Apple moved to: X = %d, Y = %d\n", falling_apple.x, falling_apple.y);

    printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");

}

/* Test score incrementer */
void test_score_increment()
{
    UINT32 *FB32 = Physbase();  
    UINT16 *FB16 = (UINT16*) Physbase();  
    score *game_score = init_score();  /* Initialize score */
    clear_screen(FB32);  /* Clear the screen initially */
    printf("Press any key to increment score up to 99\n");
    /* Display the initial score */
    printf("Initial score: %d\n", game_score->value);
    update_score(FB16, game_score);

    /* Simulate pressing the key and incrementing the score */
    while (game_score->value != 99)
    {
        /* Increment the score */
        increment_score(FB16, game_score);
        
        /* Update the score on the screen */
        update_score(FB16, game_score);
        
        Cnecin();  /* Wait for key press to increment again */
    }

printf("\nPress Numbers to Test:\n 1. Basket Movement\n 2. Apple Collision\n 3. Random Apple Position\n"
       " 4. Basket Right Border Collision\n 5. Basket Left Border Collision\n 6. Apple Movement\n"
       " 7. Score Increment\n 8. Timer Decrement\n 9. Display Message\n Q - Quit\n");

}
