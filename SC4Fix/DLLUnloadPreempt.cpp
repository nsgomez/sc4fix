/*
   Project: SC4Fix Patches for SimCity 4
   File: DLLUnloadPreempt.cpp

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

#include "DLLUnloadPreempt.h"

//--- DISABLE LIBRARY UNLOADING IN SC4 ---------------------
// Replaces a call in cGZCOMLibrary::Free to FreeLibrary
// with a no-op. SC4 won't know that any nonstandard
// DLLs are loaded, but they'll remain loaded in memory
// nonetheless.
//----------------------------------------------------------
void DLLUnloadPreempt::InstallPatch(void) {
	memset((void*)0x87B5A3, 0x90, 5);
}