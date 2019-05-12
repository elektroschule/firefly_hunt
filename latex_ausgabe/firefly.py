import serial

templatefile = 'ffhunt.tex'
outputfile = 'ffhunt-out.tex'
tty = '/dev/ttyUSB0'


ser = serial.Serial(tty)

def process_line(line):
    repl = None
    line = line.strip()
    if 'Zeit:' in line:
        print("processing", line)
        seconds = line.split(':')[1].strip()

        # looking for 'Spieler 1 hat gewonnen'
        player = '??'
        if 'gewonnen' in line:
            player = line.split('Spieler')[1].split('hat gewonnen')[0]
        repl = '\\section*{Auswertung}'
        repl += 'Spieler ' + player + ' hat gewonnen. Du hast ' + seconds + ' Sekunden benötigt, um das Glühwürmchen zu fangen. '
        repl += bewertung(int(seconds))
        update_template(repl)

    if '... Go!' in line:
        repl = 'Ein neues Spiel beginnt! Leuchte mit dem Laserpointer auf dein Glühwürmchen.\n\n' + line

    if repl is not None:
        update_template(repl)

def bewertung(sekunden):
    if 0 <= sekunden < 5:
        return "Das war sehr schnell. Hast du gemogelt?"
    elif 5 <= sekunden < 15:
        return "Du hast dir ja ganz schön Zeit gelassen."
    else:
        return "Hat ganz schön lange gedauert. "

def update_template(replacement):
    print("opening template file")
    with open(templatefile) as f:
        lines = f.read()
        lines_new = lines.replace('REPLACEME', replacement)

    print("writing template", outputfile)
    with open(outputfile, 'wt') as f:
        f.write(lines_new)

def main():
    print("STARTING")
    while True:
        line = str(ser.readline(), 'ascii')
        print(line, end='')
        process_line(line)



main()