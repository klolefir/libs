#ifndef CLI_HPP_SENTRY
#define CLI_HPP_SENTRY

class ByteArray;

static const int base_left_border_len 	= 2;
static const int base_right_border_len 	= 2;
static const int base_border_len 		= 20;
static const int max_name_len 			= 20;

static const char goodbye_msg[] = "See you later!";
static const char welcome_msg[] = "Welcome to";
static const char unknown_msg[] = "Unknown cmd";
static const char left_border_msg[] = "/==";
static const char right_border_msg[] = "==/";
static const char border_msg[] = "/==";
static const char operator_msg[] = "# ";
static const char client_msg[] = "--->";

class Cli {
protected:
	char *name;
public:
	Cli(const char *new_name);
	virtual ~Cli();
	virtual void Start() = 0;

	virtual void HandleConnect() = 0;
	virtual void PrintMenu() = 0;

	virtual void HandleExit();
	virtual void PrintWelcome();
	virtual void PrintGoodbye();
	virtual void PrintBorder(int len = base_border_len);
	virtual void PrintLeftBorder(int len = base_left_border_len);
	virtual void PrintRightBorder(int len = base_right_border_len);
	virtual void PrintOperatorInput();
	virtual void PrintClientInput();
	virtual void PrintUnknown();
	virtual void PrintHex(ByteArray &data, int offset = 0);
};

#endif
