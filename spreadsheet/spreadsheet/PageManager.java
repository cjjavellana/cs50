package spreadsheet;

import java.io.*;

/**
 * Manages the loading & persisting of matrix pages from & to disk
 */
public class PageManager {

    public Page loadPage(int pageNumber) {
        String filename = String.format("%s.dat", pageNumber);
        try {
            File file = new File(filename);
            if (file.exists()) {
                FileInputStream fis = new FileInputStream(filename);
                ObjectInputStream in = new ObjectInputStream(fis);
                return (Page) in.readObject();
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(String.format("Unable to find %s", filename), e);
        } catch (IOException e) {
            throw new RuntimeException(String.format("Unable to load %s", filename), e);
        } catch (ClassNotFoundException e) {
            throw new RuntimeException(e);
        }

        return null;
    }

    public void writePage(Page page) {
        String filename = String.format("%s.dat", page.getPageNumber());
        try {
            File file = new File(filename);
            if (file.exists()) {
                // delete previous file
                file.delete();
            }

            if (file.createNewFile()) {
                FileOutputStream fos = new FileOutputStream(file);
                ObjectOutputStream out = new ObjectOutputStream(fos);
                out.writeObject(page);
                out.close();
            } else {
                throw new RuntimeException(String.format("Unable to create new file %s", filename));
            }
        } catch (IOException e) {
            throw new RuntimeException(String.format("Unable to create new file %s", filename), e);
        }
    }
}
