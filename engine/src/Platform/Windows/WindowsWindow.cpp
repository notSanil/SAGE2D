#include "WindowsWindow.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Sage/Core/Log.h"

#include "Sage/Events/KeyEvent.h"
#include "Sage/Events/ApplicationEvent.h"
#include "Sage/Events/MouseEvent.h"
#include "Sage/Core/Keycodes.h"
#include "Sage/Core/MouseCodes.h"
#include <backends/imgui_impl_sdl.h>


namespace Sage{
	static std::unordered_map<SDL_KeyCode, KeyCode> SdlToSage;
	static std::unordered_map<int, MouseCode> SdlMouseToSage;

	void SetupKeyCodeMap()
	{
		SdlToSage[SDLK_UNKNOWN] =		KeyCode::UNKNOWN;

		SdlToSage[SDLK_RETURN] =		KeyCode::Return;
		SdlToSage[SDLK_ESCAPE] =		KeyCode::Escape;
		SdlToSage[SDLK_BACKSPACE] =		KeyCode::Backspace;
		SdlToSage[SDLK_TAB] =			KeyCode::Tab;
		SdlToSage[SDLK_SPACE] =			KeyCode::Space;
		SdlToSage[SDLK_EXCLAIM] =		KeyCode::Exclaim;
		SdlToSage[SDLK_QUOTEDBL] =		KeyCode::QuotedBL;
		SdlToSage[SDLK_HASH] =			KeyCode::Hash;
		SdlToSage[SDLK_PERCENT] =		KeyCode::Percent;
		SdlToSage[SDLK_DOLLAR] =		KeyCode::Dollar;
		SdlToSage[SDLK_AMPERSAND] =		KeyCode::Ampersand;
		SdlToSage[SDLK_QUOTE] =			KeyCode::Quote;
		SdlToSage[SDLK_LEFTPAREN] =		KeyCode::LeftParen;
		SdlToSage[SDLK_RIGHTPAREN] =	KeyCode::RightParen;
		SdlToSage[SDLK_ASTERISK] =		KeyCode::Asterisk;
		SdlToSage[SDLK_PLUS] =			KeyCode::Plus;
		SdlToSage[SDLK_COMMA] =			KeyCode::Comma;
		SdlToSage[SDLK_MINUS] =			KeyCode::Minus;
		SdlToSage[SDLK_PERIOD] =		KeyCode::Period;
		SdlToSage[SDLK_SLASH] =			KeyCode::Slash;
		SdlToSage[SDLK_0] =				KeyCode::D0;
		SdlToSage[SDLK_1] =				KeyCode::D1;
		SdlToSage[SDLK_2] =				KeyCode::D2;
		SdlToSage[SDLK_3] =				KeyCode::D3;
		SdlToSage[SDLK_4] =				KeyCode::D4;
		SdlToSage[SDLK_5] =				KeyCode::D5;
		SdlToSage[SDLK_6] =				KeyCode::D6;
		SdlToSage[SDLK_7] =				KeyCode::D7;
		SdlToSage[SDLK_8] =				KeyCode::D8;
		SdlToSage[SDLK_9] =				KeyCode::D9;
		SdlToSage[SDLK_COLON] =			KeyCode::Colon;
		SdlToSage[SDLK_SEMICOLON] =		KeyCode::SemiColon;
		SdlToSage[SDLK_LESS] =			KeyCode::Less;
		SdlToSage[SDLK_EQUALS] =		KeyCode::Equals;
		SdlToSage[SDLK_GREATER] =		KeyCode::Greater;
		SdlToSage[SDLK_QUESTION] =		KeyCode::Question;
		SdlToSage[SDLK_AT] =			KeyCode::At;

		SdlToSage[SDLK_LEFTBRACKET] =	KeyCode::LeftBracket;
		SdlToSage[SDLK_BACKSLASH] =		KeyCode::Backslash;
		SdlToSage[SDLK_RIGHTBRACKET] =	KeyCode::RightBracket;
		SdlToSage[SDLK_CARET] =			KeyCode::Caret;
		SdlToSage[SDLK_UNDERSCORE] =	KeyCode::Underscore;
		SdlToSage[SDLK_BACKQUOTE] =		KeyCode::BackQuote;
		SdlToSage[SDLK_a] =				KeyCode::a;
		SdlToSage[SDLK_b] =				KeyCode::b;
		SdlToSage[SDLK_c] =				KeyCode::c;
		SdlToSage[SDLK_d] =				KeyCode::d;
		SdlToSage[SDLK_e] =				KeyCode::e;
		SdlToSage[SDLK_f] =				KeyCode::f;
		SdlToSage[SDLK_g] =				KeyCode::g;
		SdlToSage[SDLK_h] =				KeyCode::h;
		SdlToSage[SDLK_i] =				KeyCode::i;
		SdlToSage[SDLK_j] =				KeyCode::j;
		SdlToSage[SDLK_k] =				KeyCode::k;
		SdlToSage[SDLK_l] =				KeyCode::l;
		SdlToSage[SDLK_m] =				KeyCode::m;
		SdlToSage[SDLK_n] =				KeyCode::n;
		SdlToSage[SDLK_o] =				KeyCode::o;
		SdlToSage[SDLK_p] =				KeyCode::p;
		SdlToSage[SDLK_q] =				KeyCode::q;
		SdlToSage[SDLK_r] =				KeyCode::r;
		SdlToSage[SDLK_s] =				KeyCode::s;
		SdlToSage[SDLK_t] =				KeyCode::t;
		SdlToSage[SDLK_u] =				KeyCode::u;
		SdlToSage[SDLK_v] =				KeyCode::v;
		SdlToSage[SDLK_w] =				KeyCode::w;
		SdlToSage[SDLK_x] =				KeyCode::x;
		SdlToSage[SDLK_y] =				KeyCode::y;
		SdlToSage[SDLK_z] =				KeyCode::z;
		
		SdlToSage[SDLK_CAPSLOCK] =		KeyCode::CapsLock;
		
		SdlToSage[SDLK_F1] =			KeyCode::F1;
		SdlToSage[SDLK_F2] =			KeyCode::F2;
		SdlToSage[SDLK_F3] =			KeyCode::F3;
		SdlToSage[SDLK_F4] =			KeyCode::F4;
		SdlToSage[SDLK_F5] =			KeyCode::F5;
		SdlToSage[SDLK_F6] =			KeyCode::F6;
		SdlToSage[SDLK_F7] =			KeyCode::F7;
		SdlToSage[SDLK_F8] =			KeyCode::F8;
		SdlToSage[SDLK_F9] =			KeyCode::F9;
		SdlToSage[SDLK_F10] =			KeyCode::F10;
		SdlToSage[SDLK_F11] =			KeyCode::F11;
		SdlToSage[SDLK_F12] =			KeyCode::F12;
		
		SdlToSage[SDLK_PRINTSCREEN] =	KeyCode::PrintScreen;
		SdlToSage[SDLK_SCROLLLOCK] =	KeyCode::ScrollLock;
		SdlToSage[SDLK_PAUSE] =			KeyCode::Pause;
		SdlToSage[SDLK_INSERT] =		KeyCode::Insert;
		SdlToSage[SDLK_HOME] =			KeyCode::Home;
		SdlToSage[SDLK_PAGEUP] =		KeyCode::PageUp;
		SdlToSage[SDLK_DELETE] =		KeyCode::Delete;
		SdlToSage[SDLK_END] =			KeyCode::End;
		SdlToSage[SDLK_PAGEDOWN] =		KeyCode::PageDown;
		SdlToSage[SDLK_RIGHT] =			KeyCode::Right;
		SdlToSage[SDLK_LEFT] =			KeyCode::Left;
		SdlToSage[SDLK_DOWN] =			KeyCode::Down;
		SdlToSage[SDLK_UP] =			KeyCode::Up;
		
		SdlToSage[SDLK_KP_DIVIDE] =		KeyCode::KPDivide;
		SdlToSage[SDLK_KP_MULTIPLY] =	KeyCode::KPMultiply;
		SdlToSage[SDLK_KP_MINUS] =		KeyCode::KPSubtract;
		SdlToSage[SDLK_KP_PLUS] =		KeyCode::KPAdd;
		SdlToSage[SDLK_KP_ENTER] =		KeyCode::KPEnter;
		SdlToSage[SDLK_KP_1] =			KeyCode::KP1;
		SdlToSage[SDLK_KP_2] =			KeyCode::KP2;
		SdlToSage[SDLK_KP_3] =			KeyCode::KP3;
		SdlToSage[SDLK_KP_4] =			KeyCode::KP4;
		SdlToSage[SDLK_KP_5] =			KeyCode::KP5;
		SdlToSage[SDLK_KP_6] =			KeyCode::KP6;
		SdlToSage[SDLK_KP_7] =			KeyCode::KP7;
		SdlToSage[SDLK_KP_8] =			KeyCode::KP8;
		SdlToSage[SDLK_KP_9] =			KeyCode::KP9;
		SdlToSage[SDLK_KP_0] =			KeyCode::KP0;
		
		SdlToSage[SDLK_KP_EQUALS] =		KeyCode::KPEqual;
		SdlToSage[SDLK_F13] =			KeyCode::F13;
		SdlToSage[SDLK_F14] =			KeyCode::F14;
		SdlToSage[SDLK_F15] =			KeyCode::F15;
		SdlToSage[SDLK_F16] =			KeyCode::F16;
		SdlToSage[SDLK_F17] =			KeyCode::F17;
		SdlToSage[SDLK_F18] =			KeyCode::F18;
		SdlToSage[SDLK_F19] =			KeyCode::F19;
		SdlToSage[SDLK_F20] =			KeyCode::F20;
		SdlToSage[SDLK_F21] =			KeyCode::F21;
		SdlToSage[SDLK_F22] =			KeyCode::F22;
		SdlToSage[SDLK_F23] =			KeyCode::F23;
		SdlToSage[SDLK_F24] =			KeyCode::F24;

		SdlToSage[SDLK_LGUI] =			KeyCode::LeftSuper;
		SdlToSage[SDLK_RGUI] =			KeyCode::RightSuper;
		SdlToSage[SDLK_RALT] =			KeyCode::RightAlt;
		SdlToSage[SDLK_LALT] =			KeyCode::LeftAlt;
		SdlToSage[SDLK_LCTRL] =			KeyCode::LeftControl;
		SdlToSage[SDLK_RCTRL] =			KeyCode::RightControl;
		SdlToSage[SDLK_LSHIFT] =		KeyCode::LeftShift;
		SdlToSage[SDLK_RSHIFT] =		KeyCode::RightShift;


		/////Mouse/////////
		SdlMouseToSage[SDL_BUTTON_LEFT] =	MouseCode::ButtonLeft;
		SdlMouseToSage[SDL_BUTTON_MIDDLE] = MouseCode::ButtonMiddle;
		SdlMouseToSage[SDL_BUTTON_RIGHT] =	MouseCode::ButtonRight;
		SdlMouseToSage[SDL_BUTTON_X1] =		MouseCode::Button3;
		SdlMouseToSage[SDL_BUTTON_X2] =		MouseCode::Button4;

	}


	WindowsWindow::WindowsWindow(WindowProperties& properties)
	{
		InitSDL();
		windowData.properties = properties;

		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
		flags |= properties.isFullscreen ? SDL_WINDOW_MAXIMIZED : 0;
		
		SDL_Window* window = SDL_CreateWindow(properties.name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			properties.width, properties.height, flags);
		if (window == NULL)
		{
			SAGE_CORE_CRIT("Window creation failed!");
		}		
		windowData.windowContext = window;
		SDL_DisplayMode s;
		SDL_GetWindowDisplayMode(window, &s);
		SAGE_CORE_INFO("{0} {1}", s.w, s.h);
		SetupKeyCodeMap();
	}

	WindowsWindow::~WindowsWindow()
	{
		SDL_DestroyWindow(windowData.windowContext);
		windowData.windowContext = nullptr;

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	uint32_t WindowsWindow::GetWidth()
	{
		return windowData.properties.width;
	}

	uint32_t WindowsWindow::GetHeight()
	{
		return windowData.properties.height;
	}

	std::string WindowsWindow::GetName()
	{
		return windowData.properties.name;
	}

	void WindowsWindow::SetEventCallback(EventCallbackFn function)
	{
		eventCallback = function;
	}

	void WindowsWindow::PollEvents()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			ImGui_ImplSDL2_ProcessEvent(&e);
			switch (e.type)
			{
				case SDL_KEYDOWN:
				{
					SDL_KeyCode code = (SDL_KeyCode)e.key.keysym.sym;
					if (SdlToSage.count(code) != 0)
					{
						KeyPressedEvent ev(SdlToSage[code], e.key.repeat);
						eventCallback(ev);
					}
					break;
				}
				case SDL_KEYUP:
				{
					SDL_KeyCode code = (SDL_KeyCode)e.key.keysym.sym;
					if (SdlToSage.count(code) != 0)
					{
						KeyReleasedEvent ev(SdlToSage[code]);
						eventCallback(ev);
					}
					break;
				}
				case SDL_MOUSEMOTION:
				{
					MouseMovedEvent ev((float)e.motion.x, (float)e.motion.y);
					eventCallback(ev);
					break;
				}
				case SDL_MOUSEWHEEL:
				{
					MouseScrollEvent ev(e.wheel.preciseX, e.wheel.preciseY);
					eventCallback(ev);
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					MouseButtonPressedEvent ev(SdlMouseToSage[e.button.button]);
					eventCallback(ev);
					break;
				}
				case SDL_MOUSEBUTTONUP:
				{
					MouseButtonReleasedEvent ev(SdlMouseToSage[e.button.button]);
					eventCallback(ev);
					break;
				}
				case SDL_WINDOWEVENT:
				{
					switch (e.window.event)
					{
						case SDL_WINDOWEVENT_CLOSE:
						{
							WindowCloseEvent ev;
							eventCallback(ev);
							break;
						}
						case SDL_WINDOWEVENT_RESIZED:
						{
							WindowResizeEvent ev(e.window.data1, e.window.data2);
							eventCallback(ev);
							break;
						}
					}
					break;
				}
			}
		}
	}
	void WindowsWindow::SetFullscreen(bool fullscreen)
	{
		windowData.properties.isFullscreen = fullscreen;
		Uint32 flag = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
		SDL_SetWindowFullscreen(windowData.windowContext, flag);
	}

	void WindowsWindow::InitSDL()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			SAGE_CORE_CRIT("SDL Failed to initialise!");
		}

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			SAGE_CORE_CRIT("SDL Image Failed to initialise!");
		}

		if (TTF_Init() < 0)
		{
			SAGE_CORE_CRIT("SDL TTF Failed to initialise!");
		}
	}
}