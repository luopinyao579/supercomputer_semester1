import javax.swing.*; 
import java.awt.*;
import java.text.NumberFormat; 
import java.text.ParseException; 
import java.util.concurrent.TimeUnit;

public class HeadWindow extends JFrame { 
private JTextField numberTextField; 
private JTextArea console;
private JButton startMethod; 
private JButton cleanTextArea;

public HeadWindow() {
  Font font = new Font("Times new Roman", Font.PLAIN, 16); numberTextField = new JTextField(); numberTextField.setBounds(30, 70, 150, 35); 
  numberTextField.setFont(font);
  JLabel labelNumber = new JLabel(); labelNumber.setText("Enter number"); labelNumber.setBounds(30, 20, 200, 35); labelNumber.setFont(font);
  startMethod = new JButton(); 
  startMethod.setText("Start method"); 
  startMethod.setFont(font); 
  startMethod.setBounds(250, 70, 150, 35); 
  startMethod.addActionListener(actionEvent -> {
          long startTime = System.currentTimeMillis();
      if (numberTextField.getText().isEmpty()) {
      console.append("Sorry, fill the field please\n");
    }
  else {
  Long value; 
  try {
  value = Long.valueOf(numberTextField.getText());
   }
        catch (NumberFormatException e) { 
        e.printStackTrace();
        console.append("Sorry, text is not a number\n"); return;
     }
        System.out.println(value); if(value<0) {
        console.append("Sorry, number is wrong\n");
     }
        else {
        MultithreadMethod.multithreadMethod(value.intValue());
        long endTime = System.currentTimeMillis();
        console.append("All fizzbuzz co,bination found\n");
        Console.append("Execution time:"+TimeUnit.MILLISECONDS.toSeconds(end time - starttime)+ "sec\n");
     }
   }
 }
     console = new JTextArea(); console.setBounds(30,150, 370, 250); console.setLineWrap(true); console.setWrapStyleWord(true); console.setEditable(false); 
     console.setFont(font);
     JScrollPane jScrollPane = new JScrollPane(console); jScrollPane.setBounds(30, 150, 390, 250);
     jScrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SC ROLLBAR_ALWAYS);
     cleanTextArea = new JButton(); 
     cleanTextArea.setText("Clean output"); 
     cleanTextArea.setFont(font); 
     cleanTextArea.setBounds(250, 20, 150, 35); cleanTextArea.addActionListener(actionEvent ->
     console.setText(""));

        this.add(jScrollPane); 
        this.add(cleanTextArea); 
        this.add(startMethod); 
        this.add(numberTextField); 
        this.add(labelNumber); 
        this.setTitle("FizzBuzz"); 
        this.setSize(450, 450);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE); 
        this.setLayout(null);
        this.setVisible(true);
        }
}
