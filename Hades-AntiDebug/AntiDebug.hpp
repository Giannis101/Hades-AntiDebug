
namespace Hades
{
	namespace AntiDebug
	{
		/*
		* Returns true if debugger detected.
		* Silent checks, not throwing exceptions.
		* Checking for debugging flags in self process
		*/
		bool HasDetectedProcessDebugFlags();


		/*
		* Returns true if debugger detected.
		* Silent checks, not throwing exceptions
		* Checking for debugging object handle in self process
		*/
		bool HasDetectedProcessDebugObject();


		/*
		* Returns true if debugger detected.
		* process: handle of remote process.
		* Silent checks, not throwing exceptions.
		* Checking for debugging flags in remote process
		*/
		bool HasDetectedProcessDebugFlags(
			HANDLE process
		);


		/*
		* Returns true if debugger detected.
		* process: handle of remote process.
		* Silent checks, not throwing exceptions
		* Checking for debugging object handle in remote process
		*/
		bool HasDetectedProcessDebugObject(
			HANDLE process
		);



	}
}