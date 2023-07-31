#pragma once

#ifdef USE_WIN32_WINDOWS

#define GR_VK_LBUTTON	0x01	
#define GR_VK_RBUTTON	0x02	
#define GR_VK_CANCEL	0x03	
#define GR_VK_MBUTTON	0x04	
#define GR_VK_XBUTTON1	0x05	
#define GR_VK_XBUTTON2	0x06	
#define GR_VK_BACK		0x08	
#define GR_VK_TAB		0x09	
#define GR_VK_CLEAR	0x0C
#define GR_VK_RETURN	0x0D

#define GR_VK_SHIFT	0x10	
// CTRL key
#define GR_VK_CONTROL	0x11
// ALT key
#define GR_VK_MENU		0x12	
#define GR_VK_PAUSE	0x13
// CAPS LOCK key
#define GR_VK_CAPITAL	0x14	
#define GR_VK_KANA		0x15	
#define GR_VK_HANGUEL	0x15	
#define GR_VK_HANGUL	0x15	
#define GR_VK_IME_ON	0x16	
#define GR_VK_JUNJA	0x17	
#define GR_VK_FINAL	0x18	
#define GR_VK_HANJA	0x19	
#define GR_VK_KANJI	0x19	
#define GR_VK_IME_OFF	0x1A	
#define GR_VK_ESCAPE	0x1B	
#define GR_VK_CONVERT	0x1C	
#define GR_VK_NONCONVERT	0x1D	
#define GR_VK_ACCEPT		0x1E	
#define GR_VK_MODECHANGE	0x1F	
#define GR_VK_SPACE	0x20	
#define GR_VK_PRIOR	0x21	
#define GR_VK_NEXT		0x22	
#define GR_VK_END		0x23	
#define GR_VK_HOME		0x24	
#define GR_VK_LEFT		0x25	
#define GR_VK_UP		0x26	
#define GR_VK_RIGHT	0x27	
#define GR_VK_DOWN		0x28	
#define GR_VK_SELECT	0x29	
#define GR_VK_PRINT	0x2A	
#define GR_VK_EXECUTE	0x2B	
#define GR_VK_SNAPSHOT	0x2C	
#define GR_VK_INSERT	0x2D	
#define GR_VK_DELETE	0x2E	
#define GR_VK_HELP		0x2F	
#define GR_VK_One		0x30	
#define GR_VK_Two		0x31	
#define GR_VK_Three		0x32	
#define GR_VK_Four		0x33	
#define GR_VK_Five		0x34	
#define GR_VK_Six		0x35	
#define GR_VK_Seven		0x36	
#define GR_VK_Eight		0x37	
#define GR_VK_Nine		0x38	
#define GR_VK_Zero		0x39	

#define GR_VK_A 0x41	
#define GR_VK_B 0x42	
#define GR_VK_C 0x43	
#define GR_VK_D 0x44	
#define GR_VK_E 0x45	
#define GR_VK_F 0x46	
#define GR_VK_G 0x47	
#define GR_VK_H 0x48	
#define GR_VK_I 0x49	
#define GR_VK_J 0x4A	
#define GR_VK_K 0x4B	
#define GR_VK_L 0x4C	
#define GR_VK_M 0x4D	
#define GR_VK_N 0x4E	
#define GR_VK_O 0x4F	
#define GR_VK_P 0x50	
#define GR_VK_Q 0x51	
#define GR_VK_R 0x52	
#define GR_VK_S 0x53	
#define GR_VK_T 0x54	
#define GR_VK_U 0x55	
#define GR_VK_V 0x56	
#define GR_VK_W 0x57	
#define GR_VK_X 0x58	
#define GR_VK_Y 0x59	
#define GR_VK_Z 0x5A	
#define GR_VK_LWIN	0x5B	
#define GR_VK_RWIN	0x5C	
#define GR_VK_APPS	0x5D	

#define GR_VK_SLEEP	0x5F	
#define GR_VK_NUMPAD0	0x60	
#define GR_VK_NUMPAD1	0x61	
#define GR_VK_NUMPAD2	0x62	
#define GR_VK_NUMPAD3	0x63	
#define GR_VK_NUMPAD4	0x64	
#define GR_VK_NUMPAD5	0x65	
#define GR_VK_NUMPAD6	0x66	
#define GR_VK_NUMPAD7	0x67	
#define GR_VK_NUMPAD8	0x68	
#define GR_VK_NUMPAD9	0x69	
#define GR_VK_MULTIPLY	0x6A	
#define GR_VK_ADD		0x6B	
#define GR_VK_SEPARATOR	0x6C	
#define GR_VK_SUBTRACT	0x6D	
#define GR_VK_DECIMAL	0x6E	
#define GR_VK_DIVIDE	0x6F	
#define GR_VK_F1	0x70	
#define GR_VK_F2	0x71	
#define GR_VK_F3	0x72	
#define GR_VK_F4	0x73	
#define GR_VK_F5	0x74	
#define GR_VK_F6	0x75	
#define GR_VK_F7	0x76	
#define GR_VK_F8	0x77	
#define GR_VK_F9	0x78	
#define GR_VK_F10	0x79	
#define GR_VK_F11	0x7A	
#define GR_VK_F12	0x7B	
#define GR_VK_F13	0x7C	
#define GR_VK_F14	0x7D	
#define GR_VK_F15	0x7E	
#define GR_VK_F16	0x7F	
#define GR_VK_F17	0x80	
#define GR_VK_F18	0x81	
#define GR_VK_F19	0x82	
#define GR_VK_F20	0x83	
#define GR_VK_F21	0x84	
#define GR_VK_F22	0x85	
#define GR_VK_F23	0x86	
#define GR_VK_F24	0x87	

#define GR_VK_NUMLOCK	0x90	
#define GR_VK_SCROLL	0x91	

#define GR_VK_LSHIFT	0xA0	
#define GR_VK_RSHIFT	0xA1
#define GR_VK_LCONTROL	0xA2	
#define GR_VK_RCONTROL	0xA3	
#define GR_VK_LMENU	0xA4	
#define GR_VK_RMENU	0xA5	
#define GR_VK_BROWSER_BACK	0xA6	
#define GR_VK_BROWSER_FORWARD	0xA7	
#define GR_VK_BROWSER_REFRESH	0xA8	
#define GR_VK_BROWSER_STOP		0xA9	
#define GR_VK_BROWSER_SEARCH		0xAA	
#define GR_VK_BROWSER_FAVORITES	0xAB	
#define GR_VK_BROWSER_HOME	0xAC	
#define GR_VK_VOLUME_MUTE	0xAD	
#define GR_VK_VOLUME_DOWN	0xAE	
#define GR_VK_VOLUME_UP	0xAF	
#define GR_VK_MEDIA_NEXT_TRACK	0xB0	
#define GR_VK_MEDIA_PREV_TRACK	0xB1	
#define GR_VK_MEDIA_STOP		0xB2	
#define GR_VK_MEDIA_PLAY_PAUSE	0xB3	
#define GR_VK_LAUNCH_MAIL		0xB4	
#define GR_VK_LAUNCH_MEDIA_SELECT	0xB5	
#define GR_VK_LAUNCH_APP1	0xB6	
#define GR_VK_LAUNCH_APP2	0xB7	

#define GR_VK_OEM_1	0xBA	
#define GR_VK_OEM_PLUS	0xBB	
#define GR_VK_OEM_COMMA	0xBC	
#define GR_VK_OEM_MINUS	0xBD	
#define GR_VK_OEM_PERIOD	0xBE	
#define GR_VK_OEM_2	0xBF	
#define GR_VK_OEM_3	0xC0	
#define GR_VK_OEM_4	0xDB	
#define GR_VK_OEM_5	0xDC	
#define GR_VK_OEM_6	0xDD	
#define GR_VK_OEM_7	0xDE	
#define GR_VK_OEM_8	0xDF	

#define GR_VK_OEM_102	  0xE2

#define GR_VK_PROCESSKEY 0xE5	

#define GR_VK_PACKET	0xE7

#define  GR_VK_ATTN	0xF6	
#define  GR_VK_CRSEL	0xF7	
#define  GR_VK_EXSEL	0xF8	
#define  GR_VK_EREOF	0xF9	
#define  GR_VK_PLAY	0xFA	
#define  GR_VK_ZOOM	0xFB	
#define  GR_VK_NONAME	0xFC	
#define  GR_VK_PA1		0xFD	
#define  GR_VK_OEM_CLEAR	0xFE

#else

#endif