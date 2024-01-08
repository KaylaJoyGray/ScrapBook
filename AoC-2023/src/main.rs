use std::fs::File;
use std::io::{BufRead, BufReader};
use std::path::Path;

fn day_one() -> u32 {
    let path = Path::new("./one/input");
    let file = File::open(&path).expect("Could not open file");
    let buffer = BufReader::new(file);

    let lines: Result<Vec<Vec<char>>, std::io::Error> = buffer
        .lines()
        .map(|line| line.map(|l| l.chars().collect()))
        .collect();

    let lines = lines.expect("Could not parse file");

    let mut result: u32 = 0;

    let mut first: char = '0';
    let mut last: char = '0';
    for line in lines {

        let digits:Vec<char> = line.iter().filter(|&&c| c.is_digit(10)).copied().collect();

        first = *digits.first().unwrap();

        last = match digits.iter().last() {
            Some(last_digit)=> *last_digit,
            None => first,
        };

        let mut add = String::new();
        add.push(first);
        add.push(last);

        result += add.parse::<u32>().unwrap();
    }

    result
}

fn get_num(s: &str, rev: bool) -> Option<char> {

    let of_3 = &s[0..2];
    match of_3 {
        "one" => return Some('1'),
        "two" => return Some('2'),
        "six" => return Some('6'),
        _ => (),
    }

    let of_four = &s[0..3];
    match of_four {
        "four" => return Some('4'),
        "five" => return Some('5'),
        "nine" => return Some('9'),
        _ => (),
    }

    let of_five = &s[0..4];
    match of_five {
        "three" => return Some('4'),
        "seven" => return Some('5'),
        "eight" => return Some('9'),
        _ => (),
    }

	if !rev {
		let first = s.chars().nth(0).unwrap();
		if (first.is_digit(10)) {
			return Some(first);
		}
	} else {
		let last = s.chars().nth(4).unwrap();
		if (last.is_digit(10)) {
			return Some(last);
		}
	}

    None
}
fn day_one_2() -> u32 {
    let path = Path::new("./one/input");
    let file = File::open(&path).expect("Could not open file");
    let buffer = BufReader::new(file);

    let lines: Result<Vec<String>, std::io::Error> = buffer
        .lines()
        .collect();

    let lines = lines.expect("Could not parse file");

    for line in lines {
        let mut i = 0;
        while (i < line.len()) {
            let s: &str;
			if (i+4 < line.len()) {
				s = &line[i..i+4];
			} else {
				s = &line[i..line.len()-1];
			}

			let first = get_num(s, false);

			i += 1;
        }
    }

    0
}

fn main() {
    println!("Day1 answer: {}\n", day_one());
}
