import java.util.LinkedList;

class Synchronizer {

    LinkedList<Integer> list = new LinkedList<>();
    int capacity = 3;
    int value = 0;

    public void produce() throws InterruptedException {

        synchronized (this) {
            if(list.size()==capacity)
            {
                System.out.println("Capacity of the buffer has reached");
            }
            while (list.size() == capacity)
                wait();

            System.out.println("Producer produced-" + value);

            list.add(value++);

            notify();

        }

    }

    public void consume() throws InterruptedException {

        synchronized (this) {

            if(list.size()==0)
            {
                System.out.println("buffer empty");
            }
            while (list.size() == 0)
                wait();

            int val = list.removeFirst();

            System.out.println("Consumer consumed-"
                    + val);

            notify();

        }

    }
}

class Threadexample2 {

    public static void main(String[] args)
            throws InterruptedException {

        Synchronizer s = new Synchronizer();

        Thread producer = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    while (true) {
                        s.produce();
                        Thread.sleep(2000);
                    }

                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        Thread consumer = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    while (true) {
                        s.consume();
                        Thread.sleep(5000);
                    }

                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });

        producer.start();
        consumer.start();

        producer.join();
        consumer.join();
    }

}
