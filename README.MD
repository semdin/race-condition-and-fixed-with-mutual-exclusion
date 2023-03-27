# Report

- **`Race condition and fixed with mutex`**
    
    **Race condition**
    
    <aside>
    📎 Race condition (yarış koşulu) problemi, birden fazla işlemci veya iş parçacığı tarafından paylaşılan ortak bir kaynağın (örneğin bellek, dosya vb.) eş zamanlı olarak kullanılması durumunda ortaya çıkan bir programlama hatasıdır. Bu durumda, işlemler birbirleriyle karışarak beklenmeyen sonuçlar üretebilir.
    
    C dilinde bir örnek vermek gerekirse, iki farklı iş parçacığı tarafından paylaşılan bir değişkenin aynı anda okunması ve yazılması durumunda bir race condition oluşabilir. Örneğin, aşağıdaki kodda iki iş parçacığı aynı anda "count" değişkenini artırabilir:
    
    </aside>
    
    ```c
    #include <stdio.h>
    #include <pthread.h>
    
    int count = 0;
    
    void *thread_func(void *arg){
        int i;
        for(i = 0; i < 10; i++){
            count++;
            printf("%d ", count);
        }
        printf("\n\n");
        return NULL;
    }
    
    int main(){
        pthread_t thread1, thread2;
    
        pthread_create(&thread1, NULL, thread_func, NULL);
        pthread_create(&thread2, NULL, thread_func, NULL);
    
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
    
        printf("\n\ncount = %d\n", count);
        return 0;
    }
    ```
    
    <aside>
    📎 Bu kodda, iki iş parçacığı "count" değişkenini aynı anda artırdığı için sonuç beklenmedik olabilir. Örneğin, her iki iş parçacığı da "count" değişkenini okuyup 1 artırdığında, sonuçta "count" değişkeninin beklenenden daha az bir değere sahip olması mümkündür.
    
    Bu nedenle, birden fazla işlemci veya iş parçacığı tarafından paylaşılan ortak kaynakların eş zamanlı erişimine dikkat edilmelidir. Bu tür durumlarda, senkronizasyon teknikleri (örneğin, kilitleme) kullanılarak race condition problemleri önlenebilir.
    
    </aside>
    
    **Race condition fixed with mutex**
    
    <aside>
    📎 Yukarıdaki kodda, race condition problemi çözülebilir bir şekilde güncellenebilir. Bunun için bir senkronizasyon mekanizması kullanarak, aynı anda iki iş parçacığının "count" değişkenine erişmesini engellemek gerekiyor.
    
    Bunun için C dilinde mutex (mutual exclusion) kullanılabilir. Mutex, sadece bir iş parçacığının aynı anda bir kaynağa erişmesine izin veren bir senkronizasyon mekanizmasıdır. Aşağıdaki şekilde, mutex kullanarak "count" değişkenine aynı anda sadece bir iş parçacığının erişmesini sağlayacak şekilde güncellenmiş kodu görebilirsiniz:
    
    </aside>
    
    ```c
    #include <stdio.h>
    #include <pthread.h>
    
    int count = 0;
    pthread_mutex_t mutex;
    
    void *thread_func(void *arg){
        int i;
        for(i = 0; i< 10; i++){
            pthread_mutex_lock(&mutex);
            count++;
            printf("%d ", count);
            pthread_mutex_unlock(&mutex);
        }
        printf("\n\n");
        return NULL;
    }
    
    int main(){
        pthread_t thread1, thread2;
    
        pthread_mutex_init(&mutex, NULL);
    
        pthread_create(&thread1, NULL, thread_func, NULL);
        pthread_create(&thread2, NULL, thread_func, NULL);
    
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
    
        pthread_mutex_destroy(&mutex);
    
        printf("\n\ncount = %d\n", count);
        return 0;
    }
    ```
    
    <aside>
    📎 Bu güncellenmiş kodda, "count" değişkenine erişimi senkronize etmek için bir mutex kullanılmaktadır. İş parçacıkları "count" değişkenine erişmeden önce mutex kilidini alır ve işlemlerini tamamladıktan sonra mutex kilidini serbest bırakırlar. Bu şekilde, aynı anda sadece bir iş parçacığının "count" değişkenine erişmesi sağlanır.
    
    Ayrıca, kodun başında **`pthread_mutex_t`** tipinde bir mutex tanımlanmış ve **`pthread_mutex_init`** fonksiyonu kullanılarak mutex başlatılmıştır. Mutex kullanımı bittiğinde **`pthread_mutex_destroy`** fonksiyonu ile silinmelidir.
    
    </aside>