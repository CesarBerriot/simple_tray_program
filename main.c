#include <windows.h>

#define assert(condition) do { if(!(condition)) { MessageBoxA(NULL, "assertion failed : '" #condition "'", "simple_tray_program crashed!", MB_OK | MB_ICONERROR | MB_TOPMOST); abort(); } } while(0)
#define WINDOW_CLASS_NAME "{BE65615B-CF10-4CE1-8865-8563FB8357B2}"

enum
{	WM_TRAY_ICON = WM_USER + 1,
	MENU_ABOUT = 1,
	MENU_QUIT
};

HMENU context_menu = NULL;

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

int main(void)
{	if(FindWindowA(WINDOW_CLASS_NAME, NULL))
	{	MessageBoxA(NULL, "An instance of simple_tray_program already exists!", "Failed to launch!", MB_OK | MB_ICONWARNING | MB_TOPMOST);
		return EXIT_SUCCESS;
	}

	context_menu = CreatePopupMenu();
	assert(context_menu);
	assert(AppendMenuA(context_menu, MF_STRING, MENU_ABOUT, "About"));
	assert(AppendMenuA(context_menu, MF_SEPARATOR, 0, NULL));
	assert(AppendMenuA(context_menu, MF_STRING, MENU_QUIT, "Quit"));

	WNDCLASSA window_class = { 0 };
	window_class.lpszClassName = WINDOW_CLASS_NAME;
	window_class.lpfnWndProc = window_procedure;
	assert(RegisterClassA(&window_class));

	HWND window = CreateWindowA(window_class.lpszClassName, "", 0, 0, 0, 0, 0, NULL, NULL, NULL, 0);
	assert(window);

	HICON icon = LoadIconA(NULL, IDI_INFORMATION);
	assert(icon);

	NOTIFYICONDATAA data = { 0 };
	data.cbSize = sizeof(NOTIFYICONDATAA);
	data.hWnd = window;
	data.uFlags = NIF_ICON | NIF_MESSAGE;
	data.hIcon = icon;
	data.uCallbackMessage = WM_TRAY_ICON;
	assert(Shell_NotifyIconA(NIM_ADD, &data));

	MessageBoxA(NULL, "You may now interact with simple_tray_program through its tray icon.", "It works!", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);

	MSG message;
	int get_message_result;
	while((get_message_result = GetMessageA(&message, window, 0, 0)) == TRUE)
	{	TranslateMessage(&message);
		DispatchMessageA(&message);
	}
	assert(get_message_result != -1);

	assert(Shell_NotifyIconA(NIM_DELETE, &data));

	return message.wParam;
}

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{	if(message == WM_TRAY_ICON)
	{	switch(lparam)
		{	case WM_RBUTTONUP:
			{	if(GetForegroundWindow() != window)
					assert(SetForegroundWindow(window));
				POINT cursor_position;
				assert(GetCursorPos(&cursor_position));
				int horizontal_alignment = GetSystemMetrics(SM_MENUDROPALIGNMENT) ? TPM_RIGHTALIGN : TPM_LEFTALIGN;
				int selection = TrackPopupMenu(context_menu, horizontal_alignment | TPM_BOTTOMALIGN | TPM_NONOTIFY | TPM_RETURNCMD, cursor_position.x, cursor_position.y, 0, window, NULL);
				switch(selection)
				{	case MENU_ABOUT:
						MessageBoxA(NULL, "Basically a tray icon code snippet.\nAvailable at github.com/CesarBerriot/simple_tray_program.", "About simple_tray_program", MB_OK | MB_ICONINFORMATION);
						break;
					case MENU_QUIT:
						DestroyWindow(window);
						PostQuitMessage(0);
				}
				break;
			}
		}
	}

	return DefWindowProcA(window, message, wparam, lparam);
}
