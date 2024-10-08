#include "defines.h"
#include "game.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "graphics.h"
#include "Button.h"

#include "iostream"


/*
* What is init?
*	init is a function which initializes all the pieces on the board
*	It will be used at the start of the game once , and again if the user clicks the restart button at the end of the game
* 
* What is actually going on?
*	It creates for each and every square on the board an object from the class BoardSquare which is used to represent a square on the board and saves it in a 
*	8x8 array.
* 
*/
void Game::init()
{


	//pos_x , pos_y are the coordinates of each square's center in the chess board
	float pos_x = 50.0f; //row x
	float pos_y = 50.0f; //column y


	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			
			//--------------------------------FIRST ROW - BLACK PIECES--------------------------------
			if (i == 0)
			{
				//THE 2 ROOKS
				if (j == 0 || j == 7)
				{
					board[i][j] = new BoardSquare(new Rook(pos_x, pos_y, BLACK), pos_x, pos_y , i , j);
				}


				//THE 2 KNIGHTS
				if (j == 1 || j == 6)
				{
					board[i][j] = new BoardSquare(new Knight(pos_x, pos_y, BLACK), pos_x, pos_y , i , j);
				}

				//THE 2 BISHOPS
				if (j == 2 || j == 5)
				{
					board[i][j] = new BoardSquare(new Bishop(pos_x, pos_y, BLACK), pos_x, pos_y , i , j);
				}
				
				//THE QUEEN
				if (j == 3)
				{
					board[i][j] = new BoardSquare(new Queen(pos_x, pos_y, BLACK), pos_x, pos_y , i , j);
				}

				//THE KING
				if (j == 4)
				{
					board[i][j] = new BoardSquare(new King(pos_x, pos_y, BLACK), pos_x, pos_y , i , j);

				}
			}


			//--------------------------------SECOND ROW - BLACK PAWNS--------------------------------
			if (i == 1)
			{
				board[i][j] = new BoardSquare(new Pawn(pos_x, pos_y , BLACK), pos_x, pos_y , i , j);
			}



			//--------------------------------3 - 4 - 5 - 6TH ROW - EMPTY SQUARES--------------------------------
			if (i > 1 && i < 6)
			{
				board[i][j] = new BoardSquare(nullptr , pos_x, pos_y , i , j);
			}



			//--------------------------------SEVENTH ROW - WHITE PAWNS--------------------------------
			if (i == 6)
			{
				board[i][j] = new BoardSquare(new Pawn(pos_x, pos_y , WHITE), pos_x, pos_y , i , j );
			}




			//--------------------------------EIGHTH ROW - WHITE PIECES--------------------------------
			if (i == 7)
			{
				//THE 2 ROOKS
				if (j == 0 || j == 7)
				{
					board[i][j] = new BoardSquare(new Rook(pos_x, pos_y, WHITE), pos_x, pos_y , i , j);
				}


				//THE 2 KNIGHTS
				if (j == 1 || j == 6)
				{
					board[i][j] = new BoardSquare(new Knight(pos_x, pos_y, WHITE), pos_x, pos_y , i , j);
				}

				//THE 2 BISHOPS
				if (j == 2 || j == 5)
				{
					board[i][j] = new BoardSquare(new Bishop(pos_x, pos_y, WHITE), pos_x, pos_y , i , j);
				}

				//THE QUEEN
				if (j == 3)
				{
					board[i][j] = new BoardSquare(new Queen(pos_x, pos_y, WHITE), pos_x, pos_y , i , j);
				}

				//THE KING
				if (j == 4)
				{
					board[i][j] = new BoardSquare(new King(pos_x, pos_y, WHITE), pos_x, pos_y , i , j);

				}
			}


			pos_x += 100.0f;

		}

		pos_x = 50.0f;
		pos_y += 100.0f;
	}	
}








/*
* What is draw?
*	draw is a function which is used to describe how everything looks like (board , pieces ...)
* 
* What is actually going on?
*	First of all if the state of the game is PLAYING
*		- Draw the board picture (a 800x800 png picture representing a chessboard)
*		- Draw all the squares on the board (some might not have something to draw (like the squares that has no piece in them and the cursor doesnt hover upno them)
* 
*	Then when the state goes to ENDED
*		- Draw a background
*		- Draw a text in which declares who is the winner
*		- Draw a restart button 
*/
void Game::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.outline_opacity = 0.0f;

	if (gstate == PLAYING) {


		//board
		br.texture = ASSET_PATH + std::string("chessboard.png");
		br.outline_opacity = 0.0f;
		br.fill_opacity = 1.0f;
		graphics::drawRect(CANVAS_WH / 2, CANVAS_WH / 2, CANVAS_WH, CANVAS_WH, br);


		//each square
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j]->draw();
			}
		}
	}

	if (gstate == ENDED)
	{

		
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		graphics::setFont(ASSET_PATH + std::string("SupermercadoOne-Regular.ttf"));

		graphics::drawText(50, 150, 100.0f, winner + " is the winner", br);

		restart->draw();
		
	}

		
	


	
}







/*
* What is update?
*	This function will update the state of the game for any second
* 
* What is actually going on
*	First of all if the state of the game is ENDED
*		- Check if the cursor is anywhere near the restart button and the user clicked the left button of the mouse , then restart the game
* 
*	Then... (if the game is not ENDED (it is PLAYING)) 
*		P1: Check if the player hovers on a particular square. If he does , save it in "cur_select" and highlight it -- unhighlight the rest
*		P2: Check if the user has hovered on a particular square which has a piece in it and clicked on it , save it in an another variable called "active_player" and set it active (the color of an active square is diffrent of the one that has been hovered upon)
*		P3: Check if the user is dragging a piece from a square , if he does make the piece follow the cursor wherever it goes.
*		P4: If there is an active player (A board square that has been clicked upon and has a piece on it) then ... :
*			- Get the legal moves of this particular piece for the player that has his turn
*			- Do an extra check : If the piece in the active square is a pawn then check for diagonal captures
*			- Show all the legal moves for this particular piece on the map (by enabling all the squares that the piece can go to)
*		P5: Stop showing the available squares if there is no active piece
*		P6: Check if the board square where the user has decided to let the piece fall to , is a legal move - else just return the piece from where it has been picked from
* 
*/
void Game::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);
	
	if (gstate == ENDED)
	{

		
		//highlight the button
		if (restart->contains(mx, my))
		{
			restart->setHover(true);
		}
		else
		{
			restart->setHover(false);
		}
		

		//if the button gets clicked restart the game.
		if (restart->getHover() == true && ms.button_left_pressed)
		{
			init();
			turns = WHITE_TURN;
			gstate = PLAYING;
		}

		return;
	}


	//cur_select is the variable that stores the square that has the cursor pointed upon
	BoardSquare* cur_select = nullptr;



	//P1
	//highlight all the squares that come across the cursor
	//also save the highlighted square in a variable called cur_select and unhighlight the rest
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j]->contains(mx, my))
			{
				board[i][j]->setHighlighted(true);
				cur_select = board[i][j];
			}
			else
			{
				board[i][j]->setHighlighted(false);
			}
		}
	}



	
	//P2
	//save & highlight the square that the user clicked upon (the square must have a piece)
	//and unhighlight the rest.
	if (ms.button_left_pressed && cur_select && cur_select->isThereAPiece())
	{
		active_player = cur_select;
		active_player->setActive(true);


		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (board[i][j] != active_player)
				{
					board[i][j]->setActive(false);
				}
			}
		}

	}




	//P3
	//the user is dragging an active piece
	//that means we have to take that piece wherever he moves the cursor 
	if (ms.dragging && active_player)
	{ 
		active_player->setPieceXY(mx, my);

	}


	
	
	//P4
	//This will show all the available squares for the active player
	if (active_player)
	{
		int x;
		int y;
		
		
		//All the legal moves , meaning this list will have a list of all legal squares for an active piece
		//For example the list legal_moves will be something simillar to this:
		//legal_moves = { { {1,2} , {1,3} , {3,4} }  ,  { {3,4} , {1,2} , {3,4} }  , ... 	}
		//where each list inside legal_moves is a direction of the piece (except for knight and king) and each direction 
		//inside has points (x,y) to a specific square in our board



		//WE WANT TO SHOW THE LEGAL MOVES ONLY TO THE PLAYER WHO HAS HIS TURN , the other simply will be unable to make a move until the player makes a move.
		if (active_player->getPiecePlayer() == (int)turns)
		{
			legal_moves = active_player->legalSquaresPositions(active_player->getBoardX(), active_player->getBoardY());
		}


		//we want to make a specific check for pawns only 
		//This will actually enable his two diagonal directions only if there is an enemy piece in the diagonal square
		if (active_player->getpieceID() == PAWN)
		{

			for (int i = 0; i < legal_moves.size(); i++)
			{
				if (legal_moves[i].empty()) continue;
				x = legal_moves[i][0][0];
				y = legal_moves[i][0][1];

				if (!board[x][y]->isThereAPiece() && i > 0) legal_moves[i].erase(legal_moves[i].begin() + 0); 
				if (board[x][y]->isThereAPiece() && i == 0)
				{
					legal_moves[i].erase(legal_moves[i].begin() + 0);
					if (board[x][y]->getPiece()->getMoves() == 0) printf("%d" , board[x][y]->getPiece()->getMoves());
				}
			}
		}

		
		

		for (std::vector<std::vector<int>> direction : legal_moves)
		{
			for (std::vector<int> point : direction)
			{
				x = point[0];
				y = point[1];

				//We dont want a position (x,y) simillar to the position of the piece we picked
				if (x == active_player->getBoardX() && y == active_player->getBoardY()) continue;

	
				//if the given legal square has a piece in it
				if (board[x][y]->isThereAPiece())
				{

					//if that piece is NOT knight or king 
					if (active_player->getpieceID() != 4 && active_player->getpieceID() != KNIGHT )
					{
						
						//if that legal square has a piece from our team , then break the loop (which means that for the current direction it will show no more squares)
						if (board[x][y]->getPiecePlayer() == active_player->getPiecePlayer())
						{
							break;
						}

						//if the legal square is from the opposite team , then highlight it (because we can kill it) and stop the loop (which means that for the current direction it will show no more squares)
						else
						{
							board[x][y]->setLegalMove(true);
							break;
						}
					}


					//This is specifically for knight and king , we dont want them to move somewhere where there is a piece of the same team (so we skip those squares)
					if (board[x][y]->getPiecePlayer() == active_player->getPiecePlayer())
					{
						continue;
					}
	
				}

				board[x][y]->setLegalMove(true);
			}
		}
	}




	//P5
	//This will stop showing the available squares since there is no active player
	if (!active_player)
	{
		int x;
		int y;
		for (std::vector<std::vector<int>> direction : legal_moves)
		{
			for (std::vector<int> point : direction) 
			{
				x = point[0];
				y = point[1];
				board[x][y]->setLegalMove(false);
			}
		}
		legal_moves.clear();
	}




	//P6
	//after clicking a piece user has released the left click
	if (ms.button_left_released && active_player)
	{
		

		//if the piece moved to a highlighted square and the square is legal for that piece
		if (cur_select && cur_select->isLegal())
		{


			//if there is not a piece in that square
			if (!cur_select->isThereAPiece())
			{
				cur_select->setPiece(active_player->getPiece());
				cur_select->setPieceXY(cur_select->getposX(), cur_select->getposY()); //center the piece
				cur_select->setPieceMoves();
				active_player->removePiece();
				graphics::playSound(ASSET_PATH + std::string("piece_move.mp3"), 0.5f);
				turns = turns==WHITE_TURN ? BLACK_TURN : WHITE_TURN; //change turns after the move has been played
			}

			//if there is a piece in that square
			else
			{
				//if the piece that were in the square we choose to lay our piece is of diffrent color then take it
				if (cur_select->getPiecePlayer() != active_player->getPiecePlayer())
				{
					//if anyones king gets removed , then the game is over.
					if (cur_select->getpieceID() == KING)
					{
						winner = turns == WHITE_TURN ? "White" : "Black";
						gstate = ENDED;
					}


					cur_select->deletePiece();
					cur_select->setPiece(active_player->getPiece());
					cur_select->setPieceXY(cur_select->getposX(), cur_select->getposY()); //center the piece
					cur_select->setPieceMoves();
					active_player->removePiece();
					graphics::playSound(ASSET_PATH + std::string("piece_taken.mp3"), 0.5f);
					turns = turns == WHITE_TURN ? BLACK_TURN : WHITE_TURN; //change turns after the move has been played


				}

				//if its not then reset the piece
				else
				{
					active_player->resetPieceXY();
				}
			}
		}
		
		
		//if the user moves the piece but hasnt selected a square to lay it ,then reset the piece
		if (!cur_select || !cur_select->isLegal())
		{
			active_player->resetPieceXY();
		}




		active_player->setActive(false);
		active_player = nullptr; // after doing a move remove him from active
	}

}








Game::~Game()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			delete board[i][j];
		}
	}
	if (active_player) delete active_player;
	delete restart;
}
