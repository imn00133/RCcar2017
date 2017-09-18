// SW_pin connect to digital pin, X & Y pin connected analog pin
// A0=14, A1=15 ...
const int SW_pin = 14;
const int X_pin = 15;
const int Y_pin = 16;
// X, Y border
const int border = 160;


void setup()
{
	pinMode(SW_pin, INPUT);
	digitalWrite(SW_pin, HIGH);
	Serial.begin(9600);
}

void loop()
{
	int x_value = analogRead(X_pin);
	int y_value = analogRead(Y_pin);
	int sw_value = digitalRead(SW_pin);
}

int X_axis_encoder(int x)
{
	// border = -1, border~1024-border = 0, 1024-border ~1024 = 1
	int x_value;
	if (x >= border) {
		x_value= -1;
	}
	else if (x <= (1024 - border)) {
		x_value = 1;
	}
	else {
		x_value = 0;
	}
	return x_value;
}

int Y_axis_encoder(int y)
{
	// border = -1, border~1024-border = 0, 1024-border ~1024 = 1
	int y_value;
	if (y >= border) {
		y_value = -1;
	}
	else if (y <= (1024 - border)) {
		y_value = 1;
	}
	else {
		y_value = 0;
	}
	return y_value;
}