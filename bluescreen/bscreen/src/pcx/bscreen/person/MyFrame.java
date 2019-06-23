package pcx.bscreen.person;

import java.awt.Color;
import java.awt.Toolkit;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class MyFrame extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private JLabel background;
	private ImageIcon image;
	private static Toolkit toolkit = Toolkit.getDefaultToolkit();
    // 设置窗体默认大小,使其适应屏幕大小
    public static int DEFAULE_WIDTH = (int) (toolkit.getScreenSize().getWidth() * 1.5);
    public static int DEFAULE_HEIGH = (int) (toolkit.getScreenSize().getHeight() * 1.5);
	
	public MyFrame() {
		super();
        
		addContent();
		addListener();
		
		this.setVisible(true);
	}
	private void addListener() {
		this.addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e) {
				// TODO Auto-generated method stub
				super.keyPressed(e);
				switch (e.getKeyCode()) {
				case KeyEvent.VK_ESCAPE:
					System.exit(0);
					break;
				default:
					break;
				}
			}
		});
	}
	
	private void addContent() {
		
		this.getContentPane().setBackground(Color.BLACK);
		
//		System.out.println(Thread.currentThread().getContextClassLoader().getResource(""));
		
		image = new ImageIcon("/home/chuanxing/Workspace/project/show/resources/zy.jpg");
		background = new JLabel(image);
		
		this.add(background);
//		background.setBounds(100, 100, image.getIconWidth(), image.getIconHeight());
		
		this.setUndecorated(true);
		this.setSize(MyFrame.DEFAULE_WIDTH, MyFrame.DEFAULE_HEIGH);
		this.setAlwaysOnTop(true);
		this.setResizable(false);
		this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);

	}
}
