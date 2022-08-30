#pragma once

#include <dts/Types.hpp>

#include "../DescriptorTables/InterruptRequest.hpp"
#include "../Screen/Framebuffer.hpp"

namespace Pit {

constexpr static auto PIT_MAX_HZ = 1193180;

constexpr static auto PIT_DATA_PORT0 = 0x40;
constexpr static auto PIT_DATA_PORT1 = 0x41;
constexpr static auto PIT_DATA_PORT2 = 0x42;

constexpr static auto PIT_COMMAND_PORT = 0x43;

constexpr static auto PIT_REPEAT = 0x36;

void init(dts::u32 frequency);

} // namespace Pit
