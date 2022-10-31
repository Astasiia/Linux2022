import gdb

class BreakRange (gdb.Breakpoint):
    def stop(self):
        start_value = gdb.parse_and_eval("start")
        end_value = gdb.parse_and_eval("end")
        step_value = gdb.parse_and_eval("step")
        value = gdb.parse_and_eval("i")
        if (value % 5 == 0):
            print("@@@", start_value, end_value, step_value, value)
        return False

if __name__ == '__main__':
    break_point = BreakRange('24')
    gdb.execute('run 1 12 > /dev/null')
    gdb.execute('q')
