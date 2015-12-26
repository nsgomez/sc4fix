/*
   Project: SC4Fix Patches for SimCity 4
   File: PuzzlePieceTE.h

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

#pragma once
#include "dllmain.h"
#include "patcher.h"

class PuzzlePieceTE
{
public:
	static void InstallPatch(void);

private:
	static void Hook_Sub96D8E9(void);
	static void Hook_Sub65EBA0(void);
	static void Hook_Sub65EBA0_Pt2(void);
};
