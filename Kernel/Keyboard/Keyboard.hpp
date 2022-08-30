#pragma once

#include "../DescriptorTables/InterruptRequest.hpp"
#include "../DescriptorTables/InterruptServiceRoutine.hpp"
#include "../Io/Io.hpp"
#include "../Screen/Framebuffer.hpp"
#include "KeyboardMap.hpp"

namespace Keyboard {

constexpr static auto KEYBOARD_DATA_PORT   = 0x60;
constexpr static auto KEYBOARD_STATUS_PORT = 0x64;

void init();
} // namespace Keyboard
