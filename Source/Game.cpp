#include "Game.h"
#include "Chessboard.h"
void Game::Setup(const std::string title, const sf::Vector2u& size) {
	m_windowTitle = title;
	m_windowSize = size;
	m_isDone = false;
	playerTurn = PieceColor::White;
	Active = false;
	promotion = false;
	//Create();
	SetupSounds();

	main = true;
	chessboard = false;
	after = 0;


	//sounds
	/*if (music.openFromFile("Assets/Music/Miasma.ogg")) {
		music.setVolume(200.f);
		music.setPitch(1.f);
		music.setLoop(true);
		music.play();
	}
	else std::cout << "Error!";*/


	if (font.loadFromFile("Assets/Fonts/CutiveMono-Regular.ttf")) {
		timerBlack.setFont(font);
		//timerBlack.setString("05:47");
		timerBlack.setStyle(sf::Text::Bold);
		timerBlack.setCharacterSize(40);
		timerBlack.setFillColor(sf::Color::White);
		timerBlack.setPosition(940, 100);

		timerWhite.setFont(font);
		//timerWhite.setString("07:47");
		timerWhite.setStyle(sf::Text::Bold);
		timerWhite.setCharacterSize(40);
		timerWhite.setFillColor(sf::Color::White);
		timerWhite.setPosition(940, 572); //bylo 580

	}
	else
		std::cout << "Error!\n";

	//timerW = 900;
	//timerB = 900;



	int ttimerW = timerW;
	int ttimerB = timerB;

	std::string temp0 = std::to_string(ttimerW / 60);
	std::string temp1 = std::to_string(ttimerW % 60);
	temp0.size() == 1 ? temp0 = "0" + temp0 : temp0 = temp0;
	temp1.size() == 1 ? temp1 = "0" + temp1 : temp1 = temp1;
	temp0 = { temp0 + ":" + temp1 };
	timerWhite.setString(temp0);

	temp0 = std::to_string(ttimerB / 60);
	temp1 = std::to_string(ttimerB % 60);
	temp0.size() == 1 ? temp0 = "0" + temp0 : temp0 = temp0;
	temp1.size() == 1 ? temp1 = "0" + temp1 : temp1 = temp1;
	temp0 = { temp0 + ":" + temp1 };
	timerBlack.setString(temp0);



	//sub = clock.restart();
	//std::cout << timer << std::endl;

}
void Game::Create() {
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 },
		m_windowTitle, sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(60);

}
void Game::Destroy() {
	m_window.close();
}

void Game::SetupSounds() {
	audio.loadAudio("Assets/SFX/Active1.ogg", "active");
	audio.setVolume("active", 40.f);

	audio.loadAudio("Assets/SFX/Move1.ogg", "move");
	audio.setVolume("move", 60.f);

	audio.loadAudio("Assets/SFX/Capture.ogg", "capture");
	audio.setVolume("capture", 40.f);

	audio.loadAudio("Assets/SFX/Castle.ogg", "castle");
	audio.setVolume("castle", 150.f);

	audio.loadAudio("Assets/SFX/Check0.ogg", "check");
	audio.setVolume("check", 40.f);

	audio.loadAudio("Assets/SFX/Checkmate.ogg", "checkmate");
	audio.setVolume("checkmate", 40.f);

	audio.loadAudio("Assets/SFX/Click.ogg", "click");
	audio.setVolume("click", 40.f);

	audio.loadAudio("Assets/SFX/Promotion.ogg", "promotion");
	audio.setVolume("promotion", 150.f);

	audio.loadAudio("Assets/SFX/Unactive.ogg", "unactive");
	audio.setVolume("unactive", 40.f);

	music.add("Assets/Music/we.ogg");
	music.add("Assets/Music/let.ogg");
	music.add("Assets/Music/Music1.ogg");

	music.play();
	music.setVolume(40.f);

}

void Game::SetupAfterMenu() {
	switch (after) {
	case 1: {
		afterMenu.Setup("White wins!", { 700, 400 });
		break;
	}
	case 2: {
		afterMenu.Setup("Black wins!", { 700, 400 });
		break;
	}
	case 3: {
		afterMenu.Setup("It's a draw!", { 700, 400 });
		break;
	}
	}
}

void Game::BeginDraw() { m_window.clear(sf::Color::Black); }
void Game::EndDraw() { m_window.display(); }

bool Game::IsDone() { return m_isDone; }

sf::RenderWindow* Game::GetRenderWindow() { return &m_window; }
sf::Vector2u Game::GetWindowSize() { return m_windowSize; }

void Game::Update() {
	music.next();

	//main menu window
	if (main == true) {
		mainMenu.Update();

		timerW = mainMenu.get_timer();
		timerB = mainMenu.get_timer();

		if (mainMenu.is_cplay() == true) {
			Create();
			setTime();
			mainMenu.Close();
			main = false;
			chessboard = true;
			clock.restart();
		}

		if (mainMenu.IsDone() == true) {
			m_isDone = true;
		}


	}







	//after game window---------------------------------------------

	if (after > 0) {
		afterMenu.Update();
		if (afterMenu.IsDone() == true) {
			m_isDone = true;
			afterMenu.Setup();
		}
		if (afterMenu.is_minimize() == true) {
			after = -1;
			afterMenu.Close();
			afterMenu.Setup();
		}
		if (afterMenu.is_ngame() == true) {
			m_chessboard.Initialize();
			afterMenu.ngameSetFalse();
			afterMenu.Close();
			afterMenu.Setup();
			Setup("CHESS - OOP", sf::Vector2u(1280, 720));
		}
	}


	//chesboard events---------------------------------
	if (chessboard == true) {
		updateTime();
		sf::Event event;
		//if (after == 0)
		while (m_window.pollEvent(event)) {

			switch (event.type) {
			case sf::Event::Closed: { m_isDone = true; break; }
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Escape: {m_isDone = true; break; }
				case sf::Keyboard::Right: {music.nextSong(); music.next(); break; }
				}
			case sf::Event::MouseButtonPressed:
				if (after == 0) {
					switch (event.key.code) {

					case sf::Mouse::Left: {
						//if left button is clicked

						OnClickTest();

						sf::Vector2i CurrentCoordinates = GetCellCoor();
						sf::Vector2i MouseCoordinates = sf::Mouse::getPosition(m_window);

						if (draw == true && MouseCoordinates.x > 833 + 84 && MouseCoordinates.x <= 833 + 84 * 3 &&
							MouseCoordinates.y > 318 && MouseCoordinates.y <= 402) {

							//if accepted-------------------
							if (MouseCoordinates.x <= 833 + 84 * 2) {
								draw = false;
								m_chessboard.DeactivateDraw();
								after = 3;
								SetupAfterMenu();
							}
							//if declined-------------------
							else {
								draw = false;
								m_chessboard.DeactivateDraw();
								playerTurn == PieceColor::White ? playerTurn = PieceColor::Black
									: playerTurn = PieceColor::White;
								m_chessboard.ChangeTurnSprite(playerTurn);
								changeTurnTime();
							}

						}



						if (playerTurn == PieceColor::White) {


							//surrender button
							if (MouseCoordinates.x > 1090 && MouseCoordinates.x <= 1154 &&
								MouseCoordinates.y > 569 && MouseCoordinates.y <= 633 && draw == false &&
								Active == false) {
								audio.play("click");
								std::cout << "White Player surrenders! Black wins!\n";

								after = 2;
								SetupAfterMenu();

								/*sf::sleep(sf::milliseconds(3000));
								m_isDone = true;*/
							}

							//draw button
							if (MouseCoordinates.x > 846 && MouseCoordinates.x <= 910 &&
								MouseCoordinates.y > 569 && MouseCoordinates.y <= 633 && draw == false &&
								Active == false) {
								audio.play("click");

								m_chessboard.RenderDraw();
								draw = true;

								playerTurn == PieceColor::White ? playerTurn = PieceColor::Black
									: playerTurn = PieceColor::White;
								m_chessboard.ChangeTurnSprite(playerTurn);
								changeTurnTime();

								/*after = 3;
								SetupAfterMenu();*/

							}


						}

						if (playerTurn == PieceColor::Black) {


							//surrender button
							if (MouseCoordinates.x > 1090 && MouseCoordinates.x <= 1154 &&
								MouseCoordinates.y > 96 && MouseCoordinates.y <= 160 && draw == false &&
								Active == false) {
								audio.play("click");
								std::cout << "Black Player surrenders! White wins!\n";

								after = 1;
								SetupAfterMenu();
								/*sf::sleep(sf::milliseconds(3000));
								m_isDone = true;*/
							}


							//draw button
							if (MouseCoordinates.x > 846 && MouseCoordinates.x <= 910 &&
								MouseCoordinates.y > 96 && MouseCoordinates.y <= 160 && draw == false &&
								Active == false) {
								audio.play("click");

								m_chessboard.RenderDraw();
								draw = true;

								playerTurn == PieceColor::White ? playerTurn = PieceColor::Black
									: playerTurn = PieceColor::White;
								m_chessboard.ChangeTurnSprite(playerTurn);
								changeTurnTime();

								/*after = 3;
								SetupAfterMenu();*/

							}

						}




						//promotion
						if (promotion == true && MouseCoordinates.x > 832 && MouseCoordinates.x < 1168
							&& MouseCoordinates.y>318 && MouseCoordinates.y < 402 && draw == false) {

							std::cout << "PromotionCoordinates: " << PromotionCoordinates.x << ", "
								<< PromotionCoordinates.y << std::endl;
							;
							PromotionHandler(PromotionCoordinates.y == 0 ?
								PieceColor::White : PieceColor::Black, MouseCoordinates, PromotionCoordinates);
							audio.play("promotion");
							std::cout << "Promotion\n";
							//potem zmaiana stanu na bazowy i zmiana tury, ktora nie wejdzie bo promotion bylo true
							promotion = false;
							ActiveCoord = { -1, -1 };
							Active = false;

							//Check for mate
							if (m_chessboard.CheckForCheck()) {
								if (m_chessboard.CheckForCheckmate()) {
									audio.play("checkmate");
									std::cout << "Checkmate!\n";
									m_chessboard.check == PieceColor::White ? after = 2 : after = 1;
									SetupAfterMenu();

								}

								else {
									mate = true;
									audio.play("check");
								}
							}

							playerTurn == PieceColor::White ? playerTurn = PieceColor::Black
								: playerTurn = PieceColor::White;
							m_chessboard.ChangeTurnSprite(playerTurn);
							changeTurnTime();



						}


						//if active is false, first click------------------------------------

						if (CurrentCoordinates.x >= 0 && CurrentCoordinates.x < 8
							&& CurrentCoordinates.y >= 0 && CurrentCoordinates.x < 8 && draw == false) {
							if (Active == false) {

								if (playerTurn == PieceColor::White) {


									if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Occupied
										&& m_chessboard.getPieceColor(CurrentCoordinates) == PieceColor::White) {

										Active = true;
										ActiveCoord = CurrentCoordinates;
										m_chessboard.MakeActiveSprite(ActiveCoord);
										audio.play("active");
									}
								}
								else if (playerTurn == PieceColor::Black) {
									if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Occupied
										&& m_chessboard.getPieceColor(CurrentCoordinates) == PieceColor::Black) {

										Active = true;
										ActiveCoord = CurrentCoordinates;
										m_chessboard.MakeActiveSprite(ActiveCoord);
										audio.play("active");
									}
								}
							}

							//unmake active, second click------------------------------------

							else if (Active == true && CurrentCoordinates == ActiveCoord
								&& promotion == false && draw == false) {
								m_chessboard.UnmakeActiveSprite(ActiveCoord);
								audio.play("unactive");
								ActiveCoord = { -1, -1 };
								Active = false;
							}

							//move and capture, second click------------------------------------

							else if (Active == true && CurrentCoordinates != ActiveCoord && promotion == false
								&& draw == false) {

								//move----------------------------
								if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Highlighted) {


									if (m_chessboard.getPieceID(ActiveCoord) == PieceID::King) {
										//normal move
										if (m_chessboard.getNullPtr(CurrentCoordinates)) {

											m_chessboard.UnmakeActiveSprite(ActiveCoord);
											m_chessboard.Move(ActiveCoord, CurrentCoordinates);
											audio.play("move");
										}
										//castle
										else {
											if (m_chessboard.getPieceID(CurrentCoordinates) == PieceID::Rook) {
												m_chessboard.UnmakeActiveSprite(ActiveCoord);
												if (CurrentCoordinates.x == 7) {
													m_chessboard.ShortCastle(m_chessboard.getPieceColor(ActiveCoord));
													audio.play("castle");
												}
												else {
													m_chessboard.LongCastle(m_chessboard.getPieceColor(ActiveCoord));
													audio.play("castle");

												}
											}
										}
									}
									else {
										m_chessboard.UnmakeActiveSprite(ActiveCoord);
										m_chessboard.Move(ActiveCoord, CurrentCoordinates);
										audio.play("move");
									}


									//if (mate == true) mate = false;

									//Check for mate
									if (m_chessboard.CheckForCheck()) {
										if (m_chessboard.CheckForCheckmate()) {
											audio.play("checkmate");
											std::cout << "Checkmate!\n";
											m_chessboard.check == PieceColor::White ? after = 2 : after = 1;
											SetupAfterMenu();

										}

										else {
											mate = true;
											audio.play("check");
										}
									}

									//Check for promotion
									if ((CurrentCoordinates.y == 0 || CurrentCoordinates.y == 7) &&
										m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Occupied &&
										m_chessboard.getPieceID(CurrentCoordinates) == PieceID::Pawn) {
										//m_chessboard.Promotion(PieceID::Queen, CurrentCoordinates);

										promotion = true;


										m_chessboard.RenderPromotion(
											CurrentCoordinates.y == 0 ? PieceColor::White : PieceColor::Black);

										PromotionCoordinates = CurrentCoordinates;
									}

									if (promotion == false) {
										playerTurn == PieceColor::White ? playerTurn = PieceColor::Black
											: playerTurn = PieceColor::White;
										//after = 3;
										m_chessboard.ChangeTurnSprite(playerTurn);
										changeTurnTime();

										ActiveCoord = { -1, -1 };
										Active = false;
									}

								}

								//capture-------------------------
								else if (m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Capture &&
									promotion == false) {

									audio.play("capture");
									m_chessboard.UnmakeActiveSprite(ActiveCoord);
									m_chessboard.Capture(ActiveCoord, CurrentCoordinates);





									//if (mate == true) mate = false;

									//Check for mate
									if (m_chessboard.CheckForCheck()) {
										if (m_chessboard.CheckForCheckmate()) {
											audio.play("checkmate");
											std::cout << "Checkmate!\n";
											m_chessboard.check == PieceColor::White ? after = 2 : after = 1;
											SetupAfterMenu();
											/*sf::sleep(sf::milliseconds(10'000));
											std::cin.get();
											std::cin.get();

											m_isDone = true;*/
										}

										else {
											mate = true;
											audio.play("check");
										}
									}

									//Check for promotion
									if ((CurrentCoordinates.y == 0 || CurrentCoordinates.y == 7) &&
										m_chessboard.getBoardStatus(CurrentCoordinates) == BoardStatus::Occupied &&
										m_chessboard.getPieceID(CurrentCoordinates) == PieceID::Pawn) {

										//audio.play("promotion");
										promotion = true;
										m_chessboard.RenderPromotion(CurrentCoordinates.y == 0 ?
											PieceColor::White : PieceColor::Black);

										PromotionCoordinates = CurrentCoordinates;
									}

									if (promotion == false) {
										playerTurn == PieceColor::White ? playerTurn = PieceColor::Black
											: playerTurn = PieceColor::White;
										m_chessboard.ChangeTurnSprite(playerTurn);
										changeTurnTime();

										ActiveCoord = { -1, -1 };
										Active = false;
									}


								}

								//if z promocja, bo moze zadziala wtedy z kliknieciem
							}
						}
						break;
					}
					}
				}
			}
		}
	}
}


void Game::setTime() {

	int ttimerW = timerW;
	int ttimerB = timerB;

	std::string temp0 = std::to_string(ttimerW / 60);
	std::string temp1 = std::to_string(ttimerW % 60);
	temp0.size() == 1 ? temp0 = "0" + temp0 : temp0 = temp0;
	temp1.size() == 1 ? temp1 = "0" + temp1 : temp1 = temp1;
	temp0 = { temp0 + ":" + temp1 };
	timerWhite.setString(temp0);

	temp0 = std::to_string(ttimerB / 60);
	temp1 = std::to_string(ttimerB % 60);
	temp0.size() == 1 ? temp0 = "0" + temp0 : temp0 = temp0;
	temp1.size() == 1 ? temp1 = "0" + temp1 : temp1 = temp1;
	temp0 = { temp0 + ":" + temp1 };
	timerBlack.setString(temp0);
}

int Game::GetCellNumber(sf::RenderWindow& l_window) {

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	if (mousePos.x > 23 && mousePos.x < 696 && mousePos.y>23 && mousePos.y < 695) {
		int column = (mousePos.x - 23) / cellSize;
		int row = (mousePos.y - 23) / cellSize;

		return column + row * 8;

	}
	else return -1;

}

sf::Vector2i Game::GetCellCoor()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	if (mousePos.x > 23 && mousePos.x < 696 && mousePos.y>23 && mousePos.y < 695) {
		int column = (mousePos.x - 23) / cellSize;
		int row = (mousePos.y - 23) / cellSize;

		return { column, row };

	}
	else return { -1, -1 };

}

void Game::OnClickTest() {

	if (GetCellCoor().x >= 0 && GetCellCoor().x < 8 && GetCellCoor().y >= 0 && GetCellCoor().x < 8) {
		if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Occupied) {
			int x = GetCellCoor().x;
			int y = GetCellCoor().y;

			std::cout << "Occupied: " << x << "," << y << "\n";

		}

		else if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Empty) {
			int x = GetCellCoor().x;
			int y = GetCellCoor().y;

			std::cout << "Empty: " << x << "," << y << "\n";
		}

		else if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Active) {
			int x = GetCellCoor().x;
			int y = GetCellCoor().y;

			std::cout << "Active: " << x << "," << y << "\n";
		}

		else if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Capture) {
			int x = GetCellCoor().x;
			int y = GetCellCoor().y;

			std::cout << "Capture: " << x << "," << y << "\n";

		}

		else if (m_chessboard.getBoardStatus(GetCellCoor()) == BoardStatus::Highlighted) {
			int x = GetCellCoor().x;
			int y = GetCellCoor().y;

			std::cout << "Highlighted: " << x << "," << y << "\n";
		}
	}
	else {
		int x = GetCellCoor().x;
		int y = GetCellCoor().y;
		std::cout << "None: " << x << "," << y << "\n";
	}
}

PieceID Game::getPromotionPiece(sf::Vector2i mousePos)
{
	//sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
	//if (mousePos.x > 832 && mousePos.x < 1168 && mousePos.y>318 && mousePos.y < 402) {
	switch ((mousePos.x - 832) / 84) {
	case 0: {return PieceID::Rook; break; }
	case 1: {return PieceID::Knight; break; }
	case 2: {return PieceID::Bishop; break; }
	case 3: {return PieceID::Queen; break; }
		  //default: {return PieceID::Pawn; break; }
	}
	//}

}

void Game::PromotionHandler(PieceColor color, sf::Vector2i TempCoordinates, sf::Vector2i CurrentCoordinates) {

	PieceID prom = getPromotionPiece(TempCoordinates);
	m_chessboard.Promotion(prom, CurrentCoordinates);


}

void Game::DisplayTime() {
	m_window.draw(timerWhite);
	m_window.draw(timerBlack);
}

void Game::changeTurnTime() {
	if (playerTurn == PieceColor::White) {
		timerB -= clock.getElapsedTime().asSeconds();
		clock.restart();
	}
	else {
		timerW -= clock.getElapsedTime().asSeconds();
		clock.restart();
	}

}

void Game::updateTime() {

	if (after == 0)
		if (playerTurn == PieceColor::White) {
			int ttimerW = timerW - clock.getElapsedTime().asSeconds();
			if (ttimerW <= 0) { after = 2; SetupAfterMenu(); }
			std::string temp0 = std::to_string(ttimerW / 60);
			std::string temp1 = std::to_string(ttimerW % 60);
			temp0.size() == 1 ? temp0 = "0" + temp0 : temp0 = temp0;
			temp1.size() == 1 ? temp1 = "0" + temp1 : temp1 = temp1;
			temp0 = { temp0 + ":" + temp1 };
			timerWhite.setString(temp0);
		}
		else {
			int ttimerB = timerB - clock.getElapsedTime().asSeconds();
			if (ttimerB <= 0) { after = 1; SetupAfterMenu(); }
			std::string temp0 = std::to_string(ttimerB / 60);
			std::string temp1 = std::to_string(ttimerB % 60);
			temp0.size() == 1 ? temp0 = "0" + temp0 : temp0 = temp0;
			temp1.size() == 1 ? temp1 = "0" + temp1 : temp1 = temp1;
			temp0 = { temp0 + ":" + temp1 };
			timerBlack.setString(temp0);
		}
}


Game::Game() { Setup("Chess - OOP", sf::Vector2u(1280, 720)); }
Game::Game(const std::string& title, const sf::Vector2u& size) :m_chessboard() {
	Setup(title, size);

}

Game::~Game() {}


//not used
void Game::HandleInput() {
}


void Game::Render() {
	BeginDraw();

	if (main == true) {
		mainMenu.Render();
	}

	if (chessboard == true) {
		m_chessboard.Render(m_window);
		DisplayTime();
	}
	// Render here.



	if (after > 0)
		afterMenu.Render();

	EndDraw();
}


