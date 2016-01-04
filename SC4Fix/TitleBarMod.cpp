/*
   Project: SC4Fix Patches for SimCity 4
   File: TitleBarMod.cpp

   Copyright (c) 2015 Nelson Gomez (simmaster07)

   Licensed under the MIT License. A copy of the License is available in
   LICENSE or at:

       http://opensource.org/licenses/MIT

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include "TitleBarMod.h"
#include <string>

// This is restricted to 15 characters + the null terminator
std::string szCaption("SC4Fix");

void __declspec(naked) TitleBarMod::Hook_Sub44C2B0(void) {
	_asm mov edx, offset szCaption
	RETJMP(44C99Ch);
}

void __declspec(naked) TitleBarMod::Hook_Steam_Sub44C2B0(void) {
	_asm mov ecx, offset szCaption
	RETJMP(44CA80h)
}

void TitleBarMod::InstallPatch(void) {
	switch (GetGameVersion()) {
	case 640:
		CPatcher::InstallHook(0x44C996, Hook_Sub44C2B0);
		break;

	case 641:
		CPatcher::InstallHook(0x44CA7A, Hook_Steam_Sub44C2B0);
		break;

	default:
		break;
	}

	szCaption.append(" r");
	szCaption.append(std::to_string(SC4FIX_RELEASE_VER));
}