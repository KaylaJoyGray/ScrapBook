pub fn rect_copy(mut src: &Vec<char>, mut dest: &mut Vec<char>, from_pitch: usize, to_pitch: usize, x_min: u32, y_min: u32, x_max: u32, y_max: u32, to_x: u32, to_y: u32) {
	let mut from: usize = (y_min as usize) * from_pitch + (x_min as usize);
	let mut to: usize = (to_x as usize) * to_pitch + (to_y as usize);
	let height: usize = (y_max - y_min) as usize;
	let width: usize = (x_max - x_min) as usize;

	for y in 0..height {
		for x in 0..width {
			dest[x+from] = src[x+to];
		}
		from = from + from_pitch;
		to = to + to_pitch;
	}
}

pub fn format_buffer(src: &Vec<char>, pitch: usize) -> String {
	let mut result: String = String::new();

	for (i, &c) in src.iter().enumerate() {
		if i % pitch == 0 && i != 0 {
			result.push('\n');
		}
		result.push(c);
	}
	result
}

#[cfg(test)]
mod test {
	use super::*;

	#[test]
	fn test_print_buffer() {
		let vec = vec!{'0'; 25};

		let a = format_buffer(&vec, 5);
		let b = "00000\n00000\n00000\n00000\n00000".to_string();
		assert_eq!(a, b);
		println!("{}", a);
		println!("{}", b);
	}
}