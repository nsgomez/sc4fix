/*
   Project: SC4Fix Patches for SimCity 4
   File: singleinstance.h

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

// This should never be modified or else you'll create
// conflicts between versions.
#define MUTEX_NAME "SC4Fix_{FA65A963-9315-4A2F-ADBB-4A2F36E056F5}"

BOOL NonMutexedInstanceExists(void);
BOOL ReserveInstance(void);

void HandleConflictingInstances(HMODULE hModule);
void HandleNonMutexedInstance(void);
BOOL ReleaseInstance(void);