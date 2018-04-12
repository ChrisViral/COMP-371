// Christophe Savard
// 40017812
// COMP-371 WW 
// Term Project
// April 12th 2018

#pragma once

//Forward declarations
class Mesh;

/**
 * \brief Horse animation class, also handles collision detection
 */
class Animation
{
public:
	//Enums
	/**
	 * \brief Animation state
	 */
	enum State
	{
		WALKING,
		TURNING,
		WAITING
	};

	//Constructors/destructors
	/**
	 * \brief Createsa new animation on the given Mesh objet
	 * \param mesh Mesh to animate
	 */
	explicit Animation(Mesh* mesh);
	/**
	 * \brief Copy construtor, creates a copy of the given animation on the target Mesh
	 * \param animation Animation to copy
	 * \param mesh		Mesh to animate
	 */
	Animation(const Animation& animation, Mesh* mesh);
	/**
	 * \brief Destructor, frees allocated memory
	 */
	~Animation();

	//Methods
	/**
	 * \brief Animates the mesh
	 */
	void animate();

private:
	//Fields
	Mesh* mesh;
	State state;
	float speed, steps;
	float rotSpeed, rotation;
	float waitTime;
	float progress;

	//Friends
	friend class Mesh;
};
