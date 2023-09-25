# The Royal Game of UR 
Ancient Mesopotamian board game with modern minimalist UI

![The game board](https://github.com/Pobulus/ur/assets/32367046/2120d29b-6f58-4e1a-b4f0-f71b6bc404db)
## Features
- Availables in 5 languages: English, Polish, Ukrainian, Pirate and Ancient Sumerian
- Dark mode 🌙!
- Easy explaination of the game rules
## Compiling
### Prerequisites
- This game uses [SFML](https://www.sfml-dev.org/tutorials/2.6/start-linux.php)
---
Clone this repository, navigate inside it's directory and run:
`cmake . && make`

After compilation run the executable file `gameofur`

## Gameplay
The goal of the game is to move all 7 pieces to the end of the board. 
First, each player rolls the dice to determine who should start. 
The they take turns, rolling the dice and moving a piece by the resulting number of spaces. 
If a piece lands on a _flower space_, the player gets a second roll.
If a piece lands on an enemy piece, the enemy piece is captured and returned to its starting position. 
To enter the last space, the number has to be exact.
### Controls
Click on the dice to roll them, then hover your mouse the piece you want to move, this will show you where it will land. If you wish to move the piece, click on it.
The current phase of the turn is represented by the icon in the lower left corner. It shows either the tetrahedronal dice or a piece, in the color of the current player. 


## Credits
Paweł Chmielewski - Programming, Graphics, Polish translation 

Mykyta Shemechko - UI design, Ukrainian translation, Sumerian translation
