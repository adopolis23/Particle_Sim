#pragma once
#include "SDL.h"

namespace simulation {

	class Particle {

	public:

		enum Type {
			SAND = 0
		};

		Particle(Type type, Uint16 x, Uint16 y, Uint16 width, Uint16 height);

	private:

		Type m_type;
		Uint16 m_x;
		Uint16 m_y;
		Uint16 m_width;
		Uint16 m_height;


	};


};
