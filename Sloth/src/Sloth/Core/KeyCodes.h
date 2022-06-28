#pragma once

namespace Sloth
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define SLTH_KEY_SPACE           ::Sloth::Key::Space
#define SLTH_KEY_APOSTROPHE      ::Sloth::Key::Apostrophe    /* ' */
#define SLTH_KEY_COMMA           ::Sloth::Key::Comma         /* , */
#define SLTH_KEY_MINUS           ::Sloth::Key::Minus         /* - */
#define SLTH_KEY_PERIOD          ::Sloth::Key::Period        /* . */
#define SLTH_KEY_SLASH           ::Sloth::Key::Slash         /* / */
#define SLTH_KEY_0               ::Sloth::Key::D0
#define SLTH_KEY_1               ::Sloth::Key::D1
#define SLTH_KEY_2               ::Sloth::Key::D2
#define SLTH_KEY_3               ::Sloth::Key::D3
#define SLTH_KEY_4               ::Sloth::Key::D4
#define SLTH_KEY_5               ::Sloth::Key::D5
#define SLTH_KEY_6               ::Sloth::Key::D6
#define SLTH_KEY_7               ::Sloth::Key::D7
#define SLTH_KEY_8               ::Sloth::Key::D8
#define SLTH_KEY_9               ::Sloth::Key::D9
#define SLTH_KEY_SEMICOLON       ::Sloth::Key::Semicolon     /* ; */
#define SLTH_KEY_EQUAL           ::Sloth::Key::Equal         /* = */
#define SLTH_KEY_A               ::Sloth::Key::A
#define SLTH_KEY_B               ::Sloth::Key::B
#define SLTH_KEY_C               ::Sloth::Key::C
#define SLTH_KEY_D               ::Sloth::Key::D
#define SLTH_KEY_E               ::Sloth::Key::E
#define SLTH_KEY_F               ::Sloth::Key::F
#define SLTH_KEY_G               ::Sloth::Key::G
#define SLTH_KEY_H               ::Sloth::Key::H
#define SLTH_KEY_I               ::Sloth::Key::I
#define SLTH_KEY_J               ::Sloth::Key::J
#define SLTH_KEY_K               ::Sloth::Key::K
#define SLTH_KEY_L               ::Sloth::Key::L
#define SLTH_KEY_M               ::Sloth::Key::M
#define SLTH_KEY_N               ::Sloth::Key::N
#define SLTH_KEY_O               ::Sloth::Key::O
#define SLTH_KEY_P               ::Sloth::Key::P
#define SLTH_KEY_Q               ::Sloth::Key::Q
#define SLTH_KEY_R               ::Sloth::Key::R
#define SLTH_KEY_S               ::Sloth::Key::S
#define SLTH_KEY_T               ::Sloth::Key::T
#define SLTH_KEY_U               ::Sloth::Key::U
#define SLTH_KEY_V               ::Sloth::Key::V
#define SLTH_KEY_W               ::Sloth::Key::W
#define SLTH_KEY_X               ::Sloth::Key::X
#define SLTH_KEY_Y               ::Sloth::Key::Y
#define SLTH_KEY_Z               ::Sloth::Key::Z
#define SLTH_KEY_LEFT_BRACKET    ::Sloth::Key::LeftBracket   /* [ */
#define SLTH_KEY_BACKSLASH       ::Sloth::Key::Backslash     /* \ */
#define SLTH_KEY_RIGHT_BRACKET   ::Sloth::Key::RightBracket  /* ] */
#define SLTH_KEY_GRAVE_ACCENT    ::Sloth::Key::GraveAccent   /* ` */
#define SLTH_KEY_WORLD_1         ::Sloth::Key::World1        /* non-US #1 */
#define SLTH_KEY_WORLD_2         ::Sloth::Key::World2        /* non-US #2 */

/* Function keys */
#define SLTH_KEY_ESCAPE          ::Sloth::Key::Escape
#define SLTH_KEY_ENTER           ::Sloth::Key::Enter
#define SLTH_KEY_TAB             ::Sloth::Key::Tab
#define SLTH_KEY_BACKSPACE       ::Sloth::Key::Backspace
#define SLTH_KEY_INSERT          ::Sloth::Key::Insert
#define SLTH_KEY_DELETE          ::Sloth::Key::Delete
#define SLTH_KEY_RIGHT           ::Sloth::Key::Right
#define SLTH_KEY_LEFT            ::Sloth::Key::Left
#define SLTH_KEY_DOWN            ::Sloth::Key::Down
#define SLTH_KEY_UP              ::Sloth::Key::Up
#define SLTH_KEY_PAGE_UP         ::Sloth::Key::PageUp
#define SLTH_KEY_PAGE_DOWN       ::Sloth::Key::PageDown
#define SLTH_KEY_HOME            ::Sloth::Key::Home
#define SLTH_KEY_END             ::Sloth::Key::End
#define SLTH_KEY_CAPS_LOCK       ::Sloth::Key::CapsLock
#define SLTH_KEY_SCROLL_LOCK     ::Sloth::Key::ScrollLock
#define SLTH_KEY_NUM_LOCK        ::Sloth::Key::NumLock
#define SLTH_KEY_PRINT_SCREEN    ::Sloth::Key::PrintScreen
#define SLTH_KEY_PAUSE           ::Sloth::Key::Pause
#define SLTH_KEY_F1              ::Sloth::Key::F1
#define SLTH_KEY_F2              ::Sloth::Key::F2
#define SLTH_KEY_F3              ::Sloth::Key::F3
#define SLTH_KEY_F4              ::Sloth::Key::F4
#define SLTH_KEY_F5              ::Sloth::Key::F5
#define SLTH_KEY_F6              ::Sloth::Key::F6
#define SLTH_KEY_F7              ::Sloth::Key::F7
#define SLTH_KEY_F8              ::Sloth::Key::F8
#define SLTH_KEY_F9              ::Sloth::Key::F9
#define SLTH_KEY_F10             ::Sloth::Key::F10
#define SLTH_KEY_F11             ::Sloth::Key::F11
#define SLTH_KEY_F12             ::Sloth::Key::F12
#define SLTH_KEY_F13             ::Sloth::Key::F13
#define SLTH_KEY_F14             ::Sloth::Key::F14
#define SLTH_KEY_F15             ::Sloth::Key::F15
#define SLTH_KEY_F16             ::Sloth::Key::F16
#define SLTH_KEY_F17             ::Sloth::Key::F17
#define SLTH_KEY_F18             ::Sloth::Key::F18
#define SLTH_KEY_F19             ::Sloth::Key::F19
#define SLTH_KEY_F20             ::Sloth::Key::F20
#define SLTH_KEY_F21             ::Sloth::Key::F21
#define SLTH_KEY_F22             ::Sloth::Key::F22
#define SLTH_KEY_F23             ::Sloth::Key::F23
#define SLTH_KEY_F24             ::Sloth::Key::F24
#define SLTH_KEY_F25             ::Sloth::Key::F25

/* Keypad */
#define SLTH_KEY_KP_0            ::Sloth::Key::KP0
#define SLTH_KEY_KP_1            ::Sloth::Key::KP1
#define SLTH_KEY_KP_2            ::Sloth::Key::KP2
#define SLTH_KEY_KP_3            ::Sloth::Key::KP3
#define SLTH_KEY_KP_4            ::Sloth::Key::KP4
#define SLTH_KEY_KP_5            ::Sloth::Key::KP5
#define SLTH_KEY_KP_6            ::Sloth::Key::KP6
#define SLTH_KEY_KP_7            ::Sloth::Key::KP7
#define SLTH_KEY_KP_8            ::Sloth::Key::KP8
#define SLTH_KEY_KP_9            ::Sloth::Key::KP9
#define SLTH_KEY_KP_DECIMAL      ::Sloth::Key::KPDecimal
#define SLTH_KEY_KP_DIVIDE       ::Sloth::Key::KPDivide
#define SLTH_KEY_KP_MULTIPLY     ::Sloth::Key::KPMultiply
#define SLTH_KEY_KP_SUBTRACT     ::Sloth::Key::KPSubtract
#define SLTH_KEY_KP_ADD          ::Sloth::Key::KPAdd
#define SLTH_KEY_KP_ENTER        ::Sloth::Key::KPEnter
#define SLTH_KEY_KP_EQUAL        ::Sloth::Key::KPEqual

#define SLTH_KEY_LEFT_SHIFT      ::Sloth::Key::LeftShift
#define SLTH_KEY_LEFT_CONTROL    ::Sloth::Key::LeftControl
#define SLTH_KEY_LEFT_ALT        ::Sloth::Key::LeftAlt
#define SLTH_KEY_LEFT_SUPER      ::Sloth::Key::LeftSuper
#define SLTH_KEY_RIGHT_SHIFT     ::Sloth::Key::RightShift
#define SLTH_KEY_RIGHT_CONTROL   ::Sloth::Key::RightControl
#define SLTH_KEY_RIGHT_ALT       ::Sloth::Key::RightAlt
#define SLTH_KEY_RIGHT_SUPER     ::Sloth::Key::RightSuper
#define SLTH_KEY_MENU            ::Sloth::Key::Menu