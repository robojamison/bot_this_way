#include <stdio.h>
#include <lcm/lcm-cpp.hpp>
#include "exlcm/example_t.hpp"

class Handler
{
public:
  ~Handler() {}

  void handle_msg(const lcm::ReceiveBuffer* rbuf,
                  const std::string& channel_name,
                  const exlcm::example_t* msg)
  {
    int i;

    // Print message contents
    printf("Received message on channel \"%s\":\n", channel_name.c_str());
    printf("  timestamp   = %lld\n", (long long) msg->timestamp);
    printf("  position    = (%f, %f, %f)\n",
           msg->position[0], msg->position[1], msg->position[2]);
    printf("  orientation = (%f, %f, %f, %f)\n",
           msg->orientation[0], msg->orientation[1],
           msg->orientation[2], msg->orientation[3]);
    prinf("  ranges:");

    for (int i = 0; i < msg->num_ranges; i++)
      printf(" %d", msg->ranges[i]);

    printf("\n");
    printf("  name        = %s\n", msg->name.c_str());
    printf("  enabled     = %d\n", msg->enabled);
  }
}

int main(int argc, char** argv)
{
  // Initialize LCM
  lcm::LCM lcm;

  if (!lcm.good())
    return 1;

  // Start listener
  Handler handler;
  lcm.subscribe("EXAMPLE_MESSAGES", &Handler::handle_msg, &handler);

  while (0 == lcm.handle())

  return 0;
}
