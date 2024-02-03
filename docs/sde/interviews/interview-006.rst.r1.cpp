// GlobalLogic - Lead - C++
// L1 Interview

// 3 threads
// t1  t2   t3 -> print seq {a, b, c}
// a   b    c

std::conditional_variable cv1, cv2, cv3;
std::mutex mtx(cv);

static int threads_id = 0;
static int nthreads = 3;

void thread_a(void *ch) {
	mutex_lock (mtx);
	while (cv.wait() && thread_id) {
		print(*ch);
		cv.notify_all ();
	}
	mutex_unlock (mtx);
}

for (int i = 0; i < 3;
std::

// WAP validate [(3+4)+{34-23}]

std::map m{'[': ']', '{': '}', '(': ')'};

bool parse_expr(const string &s)
{
	bool ret = true;
	std::stack st;
	for (auto c: s) {
		if (c == '[' || c == '{' || c == '(')
			st.push(c);
		else if (c == ']' || c == '}' || c == ')')
			 if (m[st.pop()] != c) {
				ret = false;
			 	break
			 }
	}
	return ret;
}

---
