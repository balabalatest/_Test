--SDL��ʼ������
SDL_INIT_TYPE = 
{
	SDL_INIT_VIDEO = tonumber("00000020", 16),--��16�����ַ���ת����10��������
}

--SDL��������
SDL_WINDOW_TYPE = 
{
	SDL_WINDOW_FULLSCREEN = tonumber("00000001", 16),
}

SDL_RENDERER_TYPE = 
{
	SDL_RENDERER_ACCELERATED = tonumber("00000002", 16),
	SDL_RENDERER_PRESENTVSYNC = tonumber("00000004", 16),
}

--SDL_Image��ʼ������
SDL_IMAGE_INIT_TYPE = 
{
	IMG_INIT_PNG = tonumber("00000002", 16),
}

--�¼�����
SDL_EVENT_TYPE = 
{
	SDL_QUIT = tonumber("100", 16),
}

--����
SDL_KEYCODE = 
{
	SDL_SCANCODE_A = 4,
    SDL_SCANCODE_B = 5,
    SDL_SCANCODE_C = 6,
    SDL_SCANCODE_D = 7,
    SDL_SCANCODE_E = 8,
    SDL_SCANCODE_F = 9,
    SDL_SCANCODE_G = 10,
    SDL_SCANCODE_H = 11,
    SDL_SCANCODE_I = 12,
    SDL_SCANCODE_J = 13,
    SDL_SCANCODE_K = 14,
    SDL_SCANCODE_L = 15,
    SDL_SCANCODE_M = 16,
    SDL_SCANCODE_N = 17,
    SDL_SCANCODE_O = 18,
    SDL_SCANCODE_P = 19,
    SDL_SCANCODE_Q = 20,
    SDL_SCANCODE_R = 21,
    SDL_SCANCODE_S = 22,
    SDL_SCANCODE_T = 23,
    SDL_SCANCODE_U = 24,
    SDL_SCANCODE_V = 25,
    SDL_SCANCODE_W = 26,
    SDL_SCANCODE_X = 27,
    SDL_SCANCODE_Y = 28,
    SDL_SCANCODE_Z = 29,

    SDL_SCANCODE_1 = 30,
    SDL_SCANCODE_2 = 31,
    SDL_SCANCODE_3 = 32,
    SDL_SCANCODE_4 = 33,
    SDL_SCANCODE_5 = 34,
    SDL_SCANCODE_6 = 35,
    SDL_SCANCODE_7 = 36,
    SDL_SCANCODE_8 = 37,
    SDL_SCANCODE_9 = 38,
    SDL_SCANCODE_0 = 39,

    SDL_SCANCODE_RETURN = 40,
    SDL_SCANCODE_ESCAPE = 41,
    SDL_SCANCODE_BACKSPACE = 42,
    SDL_SCANCODE_TAB = 43,
    SDL_SCANCODE_SPACE = 44,
}