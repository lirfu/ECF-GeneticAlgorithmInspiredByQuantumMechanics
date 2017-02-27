#include <ecf/ECF.h>

int main(int argc, char **argv) {
	StateP state(new State);

	state->initialize(argc, argv);
	state->run();
}
