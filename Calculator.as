import gui

gui.title("Калькулятор")

let history = []

func calc(a, b, op) {
    if op == "+" { return a + b }
    if op == "-" { return a - b }
    if op == "*" { return a * b }
    if op == "/" { 
        if b == 0 {
            gui.error("Деление на ноль")
            return 0
        }
        return a / b
    }
    gui.error("Неизвестная операция")
    return 0
}

gui.success("Калькулятор запущен")

let running = 1
while running {
    let expr = gui.input("Введи выражение (число операция число) или exit: ")
    
    if expr == "exit" {
        running = 0
    } elif expr == "hist" {
        if len(history) == 0 {
            gui.color("yellow", "История пуста")
        } else {
            gui.color("cyan", "=== История ===")
            for i in 0..len(history) {
                gui.color("white", history[i])
            }
        }
    } else {
        let parts = expr.split(" ")
        if len(parts) == 3 {
            let a = num(parts[0])
            let b = num(parts[2])
            let op = parts[1]
            let res = calc(a, b, op)
            let line = a + " " + op + " " + b + " = " + res
            gui.color("green", line)
            history.append(line)
        } else {
            gui.error("Неверный формат. Пример: 10 + 5")
        }
    }
}

          gui.success("До свидания!")
          // алькукальа
