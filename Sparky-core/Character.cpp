#include "Character.h"
#include <iostream>

//initializing the defalut constructor values
Character::Character(std::string name, glm::vec2 pos, int person, glm::vec2 dim, float speed, const std::vector<std::string>& levelData)
{
	m_health = 1;
	m_name = name;
	m_position = pos;
	m_person = person;
	m_dim = dim;
	m_speed = speed;
	m_texId = ResourceManager::getTexture(m_filePaths[m_person]).id;
	m_levelData = levelData;
	m_score = -1;
	gunID = 1;
}

Character::~Character()
{
}

//setting the attributes of the character
void Character::setData(float x, float y, int health)
{
	m_position.x = x;
	m_position.y = y;
	m_health = health;
}

void Character::nitro()
{
	if (m_health > 0)
	{
		
		if(!timer_nitro)
			m_speed =  m_speed * 2;
		timer_nitro += 100;
		
		m_health--;
	}
}

//setting the heart to take 
void Character::setHeart(int heart)
{
	m_score = heart;
}

//the damage taken by the player on being hit by a bullet
bool Character::damageTaken(int damage, int livePlayers, int callerPlayer, int playerType)
{
	m_health -= damage;
	if (m_health <= 0)
	{
		if (callerPlayer == playerType && life == true)
			std::cout << m_name << " You are dead and Your Rank is :  " << livePlayers << std::endl;
		return true;
	}
	return false;
}

void Character::setDefaultSpeed()
{
	m_speed = m_speed / 2;
}

void Character::setDefaultSpeedBlack()
{
	m_speed = m_speed * 2;
}

//func to increase health
void Character::increaseHealth()
{
	if (m_health < 7)
		m_health++;
}

void Character::decHealth()
{
	if(!timer_slow)
	m_speed = m_speed / 2;
	timer_slow = 150;
}

//function to get data
std::string Character::getData()
{
	std::string result = std::to_string(m_position.x) + " " + std::to_string(m_position.y) + "|" + std::to_string(m_health) + "|" + std::to_string(m_score) + "|";
	return result;
}

//function to draw the sprites
void Character::draw(SpriteBatch& spriteBatch)
{
	spriteBatch.draw(glm::vec4(m_position.x, m_position.y, m_dim.x, m_dim.y), m_uv, m_texId, 0.0f, m_color);
}

//function to move the characters

void Character::moveUP(int vertical_speed)
{
	/*if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][ceil((m_position.y + m_dim.y) / (float)TILE_WIDTH)] != '.') ||
		(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][ceil((m_position.y + m_dim.y) / (float)TILE_WIDTH)] != '.'))		//wall above somewhere
	{
		int distance = ((int)(m_position.y + m_dim.y)) % TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
			m_time_rem = 0;
			return; //without updating the position, as the player cannot move any closer than the min distance 
		}
	}*/

	float y_pos, x_pos;
	m_vertical_speed = vertical_speed;

		if (m_hasReachedGround) {
			m_time_rem = 0;
			air_pos_x = m_position.x;
			air_pos_y = m_position.y;
			c1 = false;
			c2 = false;
			m_hasReachedGround = false;
		}
		else {
			// m_vertical_speed = 10 + m_gravity * (tmp - m_time_rem);
			if (m_first_time) {
				m_time_rem = 0;
				air_pos_x = m_position.x;
				air_pos_y = m_position.y;
				c1 = false;
				c2 = false;
				m_first_time = false;
			}

			x_pos = h_speed * (m_time_rem);
			y_pos = m_vertical_speed * (m_time_rem) + (m_gravity * (m_time_rem) * (m_time_rem)) / 100;
			m_time_rem++;

			

			float fut_x = air_pos_x + x_pos ;
			float fut_y = air_pos_y + y_pos ;
			
			float fut_posx = fut_x;
			float fut_posy = fut_y;

			if (c2)
			{
				fut_posx = m_position.x;
			}
			if (c1)
			{
				fut_posy = m_position.y;
			}

			// std::cout << "remain time " << m_time_rem << std::endl;

			

			if (m_direction == 1 && !c1 && ((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] != '.') ||
				(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] != '.')))		//wall above somewhere
			{
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 'S') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 'S')))
				{
					int distance = ((int)(fut_posy + m_dim.y)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						m_position = glm::vec2(130.0f, 48.0f);
						m_hasReachedGround = true;
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 's') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 's')))
				{
					int distance = ((int)(fut_posy + m_dim.y)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						m_position = glm::vec2(130.0f, 48.0f);
						m_hasReachedGround = true;
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 'l') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 'l')))
				{
					int distance = ((int)(fut_posy + m_dim.y)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						m_position = glm::vec2(130.0f, 48.0f);
						m_hasReachedGround = true;
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == '+') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == '+')))
				{
					int distance = ((int)(fut_posy + m_dim.y)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						m_position = glm::vec2(130.0f, 48.0f);
						m_hasReachedGround = true;
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == '-') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][ceil((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == '-')))
				{
					int distance = ((int)(fut_posy + m_dim.y)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						m_position = glm::vec2(130.0f, 48.0f);
						m_hasReachedGround = true;
						return;
					}

				}
				// std::cout << "Going to change y " << std::endl;
				int distance = ((int)(fut_posy + m_dim.y)) % TILE_WIDTH;
				if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
					fut_posy = m_position.y;
					m_is_called_by = 1;
					m_first_time = true;
					c1 = true;
					m_direction = -1;
					//std::cout << "Collision with upper wall detected.\n";
					//m_time_rem = 0;
					//return; //without updating the position, as the player cannot move any closer than the min distance 
				}


			}

			
			if (floor(fut_posx / (float)TILE_WIDTH) < 0 || floor((fut_posx + m_dim.x) / (float)TILE_WIDTH) < 0 || floor((fut_posy) / (float)TILE_WIDTH) - 1 < 0 || floor((fut_posy) / (float)TILE_WIDTH) - 1 < 0)
			{
				m_hasReachedGround = true;
				m_direction = 0;
				return;
			}

			/*for (int i = floor((m_position.y) / (float)TILE_WIDTH) - 1; i < floor((fut_posy) / (float)TILE_WIDTH) - 1; i++)
			{

			}*/
			if (!c1 && ((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] != '.') ||
				(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] != '.'))) //wall below somewhere
			{
				// to respawn when collision occured with spike in right direction
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == 'S') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == 'S')))
				{
					int distance = ((int)(fut_posy)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == 's') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == 's')))
				{
					int distance = ((int)(fut_posy)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == 'l') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == 'l')))
				{
					int distance = ((int)(fut_posy)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == '+') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == '+')))
				{
					int distance = ((int)(fut_posy)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == '-') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == '-')))
				{
					int distance = ((int)(fut_posy)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}

				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == 'G') ||
					(m_levelData[floor((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH) - 1] == 'G')))
				{
					int distance = ((int)(fut_posy)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_is_called_by = 0;
						m_first_time = true;
						m_direction = 1;
						return;
					}
				}

				// std::cout << "Going to change yyy " << std::endl;
				int distance = ((int)(fut_posy)) % TILE_WIDTH;
				if (distance < MIN_WALL_DISTANCE) {
					m_hasReachedGround = true;
					//std::cout << "Collision with lower wall detected.\n";
					c1 = true;
					fut_posy = m_position.y;
					m_direction = 0;
					//m_time_rem = 0;
					//return; //without updating the position, as the player cannot move any closer than the min distance 

				}


			}

			if (!c2 && ((m_levelData[floor(fut_posx / (float)TILE_WIDTH) - 1][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] != '.') ||
				(m_levelData[floor((fut_posx) / (float)TILE_WIDTH) - 1][floor((fut_posy) / (float)TILE_WIDTH)] != '.')))	//wall on the left somehwere
			{
				// to respawn when collision occured with spike in right direction
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH) - 1][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 'S') ||
					(m_levelData[floor((fut_posx) / (float)TILE_WIDTH) - 1][floor((fut_posy) / (float)TILE_WIDTH)] == 'S')))
				{
					int distance = ((int)(fut_posx)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH) - 1][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 's') ||
					(m_levelData[floor((fut_posx) / (float)TILE_WIDTH) - 1][floor((fut_posy) / (float)TILE_WIDTH)] == 's')))
				{
					int distance = ((int)(fut_posx)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH) - 1][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 'l') ||
					(m_levelData[floor((fut_posx) / (float)TILE_WIDTH) - 1][floor((fut_posy) / (float)TILE_WIDTH)] == 'l')))
				{
					int distance = ((int)(fut_posx)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH) - 1][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == '+') ||
					(m_levelData[floor((fut_posx) / (float)TILE_WIDTH) - 1][floor((fut_posy) / (float)TILE_WIDTH)] == '+')))
				{
					int distance = ((int)(fut_posx)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[floor(fut_posx / (float)TILE_WIDTH) - 1][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == '-') ||
					(m_levelData[floor((fut_posx) / (float)TILE_WIDTH) - 1][floor((fut_posy) / (float)TILE_WIDTH)] == '-')))
				{
					int distance = ((int)(fut_posx)) % TILE_WIDTH;
					if (distance < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}

				int distance = ((int)(fut_posx)) % TILE_WIDTH;
				if (distance < MIN_WALL_DISTANCE) {
					c2 = true;
					std::cout << "Collision with right wall detected.\n";
					fut_posx = m_position.x;
					//m_time_rem = 0;
					//return; //without updating the position, as the player cannot move any closer than the min distance 

				}


			}

			if (!c2 && ((m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] != '.') ||
				(m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH)] != '.')))	//wall on the right
			{
				// to respawn when collision occured with spike in right direction
				if (((m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 'S') ||
					(m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH)] == 'S')))
				{
					int distance = ((int)(fut_posx + m_dim.x)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if ((m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == 'E') ||
					(m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)] == 'E')) {
					int distance = ((int)(m_position.x + m_dim.x)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						life = false;
						std::cout << "Setting false" << std::endl;
					}
				}
				if (((m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 's') ||
					(m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH)] == 's')))
				{
					int distance = ((int)(fut_posx + m_dim.x)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == 'l') ||
					(m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH)] == 'l')))
				{
					int distance = ((int)(fut_posx + m_dim.x)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == '+') ||
					(m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH)] == '+')))
				{
					int distance = ((int)(fut_posx + m_dim.x)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}
				if (((m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy + m_dim.y) / (float)TILE_WIDTH)] == '-') ||
					(m_levelData[ceil((fut_posx + m_dim.x) / (float)TILE_WIDTH)][floor((fut_posy) / (float)TILE_WIDTH)] == '-')))
				{
					int distance = ((int)(fut_posx + m_dim.x)) % TILE_WIDTH;
					if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
						m_hasReachedGround = true;
						m_position = glm::vec2(130.0f, 48.0f);
						return;
					}

				}

				int distance = ((int)(fut_posx + m_dim.x)) % TILE_WIDTH;
				if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE)
				{
					c2 = true;
					fut_posx = m_position.x;
					//m_time_rem = 0;
					//return;	//without updating the position, as the player cannot move any closer than the min distance 
				}

			}

			if (c1 == true) {
				fut_posy = m_position.y;
				// std::cout << " c1 taking x pos = " << fut_posx << std::endl;
				// std::cout << " c1 taking y pos = " << fut_posy << std::endl;
			}
				
			if (c2 == true) {
				fut_posx = m_position.x;
				// std::cout << " c2 taking x pos = " << fut_posx << std::endl;
				// std::cout << " c2 taking y pos = " << fut_posy << std::endl;
			}

			//std::cout << "Going to increment xpos = "<< m_position.x << ", ypos = " << m_position.y << std::endl;
			m_position = glm::vec2(fut_posx, fut_posy);
			//m_position = glm::vec2(air_pos_x + x_pos, air_pos_y + y_pos);
		}

	return;
}

void Character::moveDOWN()
{
	if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] != '.') ||
		(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] != '.')) //wall below somewhere
	{
		int distance = ((int)(m_position.y)) % TILE_WIDTH;
		if (distance < MIN_WALL_DISTANCE)
			return; //without updating the position, as the player cannot move any closer than the min distance 
	}
	m_position += glm::vec2(0.0f, -m_speed);
	return;
}

void Character::moveLEFT()
{	
	if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH) - 1][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == 'S') ||
		(m_levelData[floor((m_position.x) / (float)TILE_WIDTH) - 1][floor((m_position.y) / (float)TILE_WIDTH)] == 'S'))	//wall on the left somehwere
	{
		int distance = ((int)(m_position.x)) % TILE_WIDTH;
		if (distance < MIN_WALL_DISTANCE)
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
	}
	if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH) - 1][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == 's') ||
		(m_levelData[floor((m_position.x) / (float)TILE_WIDTH) - 1][floor((m_position.y) / (float)TILE_WIDTH)] == 's'))	//wall on the left somehwere
	{
		int distance = ((int)(m_position.x)) % TILE_WIDTH;
		if (distance < MIN_WALL_DISTANCE)
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
	}
	if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH) - 1][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == 'l') ||
		(m_levelData[floor((m_position.x) / (float)TILE_WIDTH) - 1][floor((m_position.y) / (float)TILE_WIDTH)] == 'l'))	//wall on the left somehwere
	{
		int distance = ((int)(m_position.x)) % TILE_WIDTH;
		if (distance < MIN_WALL_DISTANCE)
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
	}
	if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH) - 1][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == '+') ||
		(m_levelData[floor((m_position.x) / (float)TILE_WIDTH) - 1][floor((m_position.y) / (float)TILE_WIDTH)] == '+'))	//wall on the left somehwere
	{
		int distance = ((int)(m_position.x)) % TILE_WIDTH;
		if (distance < MIN_WALL_DISTANCE)
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
	}
	if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH) - 1][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == '-') ||
		(m_levelData[floor((m_position.x) / (float)TILE_WIDTH) - 1][floor((m_position.y) / (float)TILE_WIDTH)] == '-'))	//wall on the left somehwere
	{
		int distance = ((int)(m_position.x)) % TILE_WIDTH;
		if (distance < MIN_WALL_DISTANCE)
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
	}

	if ((m_levelData[floor(m_position.x / (float)TILE_WIDTH) - 1][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] != '.') ||
		(m_levelData[floor((m_position.x) / (float)TILE_WIDTH) - 1][floor((m_position.y) / (float)TILE_WIDTH)] != '.'))	//wall on the left somehwere
	{
		int distance = ((int)(m_position.x)) % TILE_WIDTH;
		if (distance < MIN_WALL_DISTANCE)
			return; //without updating the position, as the player cannot move any closer than the min distance 
	}
	h_speed = -m_speed;
	if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] != '.') ||
		(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] != '.'))) //wall below somewhere
	{

		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'G') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'G'))) //wall below somewhere
		{
			m_hasReachedGround = false;
			m_is_called_by = 0;
			m_first_time = true;
			m_direction = 1;
			return;
		}
		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'S') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'S'))) //wall below somewhere
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 's') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 's'))) //wall below somewhere
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'l') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'l'))) //wall below somewhere
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == '+') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == '+'))) //wall below somewhere
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == '-') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == '-'))) //wall below somewhere
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
		// std::cout << "x index = " << floor(m_position.x / (float)TILE_WIDTH) << ", y index = " << floor(m_position.y / (float)TILE_WIDTH) - 1 << std::endl;
		is_d_pressed = true;
		m_position += glm::vec2(-m_speed, 0.0f);
	}
	else {
		// std::cout << "going...else\n";
		m_hasReachedGround = false;
		m_is_called_by = 1;
		m_first_time = true;
	}

	return;
}


void Character::moveRIGHT()
{
	if ((m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == 'S') ||
		(m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)] == 'S')) {
		int distance = ((int)(m_position.x + m_dim.x)) % TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
	}

	if ((m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == 'E') ||
		(m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)] == 'E')) {
		int distance = ((int)(m_position.x + m_dim.x)) % TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
			life = false;
			//std::cout << "Setting false" << std::endl;
		}
	}
	if ((m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == 's') ||
		(m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)] == 's')) {
		int distance = ((int)(m_position.x + m_dim.x)) % TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
	}
	if ((m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == 'l') ||
		(m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)] == 'l')) {
		int distance = ((int)(m_position.x + m_dim.x)) % TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
	}
	if ((m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == '+') ||
		(m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)] == '+')) {
		int distance = ((int)(m_position.x + m_dim.x)) % TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
	}
	if ((m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] == '-') ||
		(m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)] == '-')) {
		int distance = ((int)(m_position.x + m_dim.x)) % TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE) {
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
	}


	if ((m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y + m_dim.y) / (float)TILE_WIDTH)] != '.') ||
		(m_levelData[ceil((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH)] != '.'))	//wall on the right
	{
		int distance = ((int)(m_position.x + m_dim.x)) % TILE_WIDTH;
		if ((TILE_WIDTH - distance) < MIN_WALL_DISTANCE)
			return;	//without updating the position, as the player cannot move any closer than the min distance 
	}
	h_speed = m_speed;

	if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] != '.') ||
				(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] != '.'))) //wall below somewhere
	{

		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'G') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'G'))) //wall below somewhere
		{
			m_hasReachedGround = false;
			m_is_called_by = 0;
			m_first_time = true;
			m_direction = 1;
			return;
		}
		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'S') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'S'))) //wall below somewhere
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 's') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 's'))) //wall below somewhere
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'l') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == 'l'))) //wall below somewhere
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == '+') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == '+'))) //wall below somewhere
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}
		if (((m_levelData[floor(m_position.x / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == '-') ||
			(m_levelData[floor((m_position.x + m_dim.x) / (float)TILE_WIDTH)][floor((m_position.y) / (float)TILE_WIDTH) - 1] == '-'))) //wall below somewhere
		{
			m_position = glm::vec2(130.0f, 48.0f);
			return;
		}

		// std::cout << "x index = " << floor(m_position.x / (float)TILE_WIDTH) << ", y index = " << floor(m_position.y / (float)TILE_WIDTH) - 1 << std::endl;
		is_d_pressed = true;
		m_position += glm::vec2(m_speed, 0.0f);
	}
	else {
		// std::cout << "going...else\n";
		//std::cout << "No wall below detected.\n";
		m_hasReachedGround = false;
		m_is_called_by = 1;
		m_first_time = true;
	}

	return;
}
