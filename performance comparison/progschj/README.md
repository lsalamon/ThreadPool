# Environment
CPU: intel i7 4930k<br>
OS: windows 7 enterprise sp1, 64 bit<br>
Compiler: visual c++ 2015<br>
Compiler Option: release, x64, full optimization<br>
Iteration: 10000000<br>
Thread Count: 12
# Result
	progschj
		each spends 532306 nanoseconds on test_progschj_ctor_and_dtor
		each spends 23359 nanoseconds on test_progschj_specific_N
		each spends 1988 nanoseconds on test_progschj_billion
# Compare To Fdhvdu
About construction and destruction time, progschj's threadpool is slower than Fdhvdu's threadpool<br>
About waiting specific job to complete, progschj's threadpool is slower than Fdhvdu's threadpool<br>
About given a number of jobs, progschj's threadpool is slower than Fdhvdu's CThreadPool<br><br>
As a result, you should use Fdhvdu's CThreadPool in any condition
