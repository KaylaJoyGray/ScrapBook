use std::io;
use std::io::stderr;
use crossterm::execute;
use crossterm::terminal::{disable_raw_mode, enable_raw_mode, EnterAlternateScreen, LeaveAlternateScreen};

pub struct Term;

impl Term {
	pub fn new() -> Result<Self, io::Error> {
		enable_raw_mode()?;
		execute!(stderr(), EnterAlternateScreen)?;
		Ok(Self)
	}

	fn exit() -> Result<(), io::Error> {
		execute!(stderr(), LeaveAlternateScreen)?;
		disable_raw_mode()?;
		Ok(())
	}
}

impl Drop for Term {
	fn drop(&mut self) {
		if let Err(err) = Term::exit() {
			eprintln!("Error during terminal shutdown: {}", err);
		}
	}
}