function first() {
    var cnt = 10
    function second() {
        let cnt = 121
        function third() {
            cnt++;

            console.log(cnt)
        }

        return third;

    }
    cnt = 25
    return second();
}

const func = first();
func()
func()
func()
func()
func()
func()

