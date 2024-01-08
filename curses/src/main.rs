mod app;
mod term;

use std::io::{stdout, Result};
use crossterm::{
    event,
    event::*,
    terminal::*,
    ExecutableCommand,
};
use ratatui::prelude::*;
use ratatui::widgets::Paragraph;

fn main() -> Result<()> {
    stdout().execute(EnterAlternateScreen)?;
    enable_raw_mode()?;
    let mut terminal = Terminal::new(CrosstermBackend::new(stdout()))?;
    terminal.clear()?;

    loop {
        terminal.draw(|frame| {
           let area = frame.size();

            frame.render_widget(
                Paragraph::new("Hello World! (press q to quit)")
                    .white()
                    .on_blue(),
                area,
            );
        })?;

        if event::poll(std::time::Duration::from_millis(16))? {
            if let event::Event::Key(key) = event::read()? {
                if key.kind == KeyEventKind::Press && key.code == KeyCode::Char('q') {
                    break;
                }
            }
        };
    }


    stdout().execute(LeaveAlternateScreen)?;
    disable_raw_mode()?;
    Ok(())
}
