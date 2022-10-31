import gdb

class BreakRange (gdb.Breakpoint):
    count_elem = 0
    def stop(self):
        start_value = gdb.parse_and_eval("start")
        end_value = gdb.parse_and_eval("end")
        step_value = gdb.parse_and_eval("step")
        value = gdb.parse_and_eval("i")
        self.count_elem = self.count_elem + 1
        if (self.count_elem > 27) & (self.count_elem < 36):
            print("@@@", start_value, end_value, step_value, value)
        return False

if __name__ == '__main__':
    break_point = BreakRange('24')
    gdb.execute('run -100 100 3 > /dev/null')
    gdb.execute('q')
