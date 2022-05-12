#include<iostream>
#define SPACE 10

using namespace std;

class pohonNode {
  public:
    int nilai;
  	pohonNode * kiri;
  	pohonNode * kanan;

  pohonNode() {
    nilai = 0;
    kiri = NULL;
    kanan = NULL;
  }
  pohonNode(int v) {
    nilai = v;
    kiri = NULL;
    kanan = NULL;
  }
};

class BST {
  public:
    pohonNode * root;
  BST() {
    root = NULL;
  }
  bool isTreeEmpty() {
    if (root == NULL) {
      return true;
    } else {
      return false;
    }
  }

  void insertNode(pohonNode * node_baru) {
    if (root == NULL) {
      root = node_baru;
      cout << "Nilai Di Inputkan Sebagai Root Node!" << endl;
    } else {
      pohonNode * temp = root;
      while (temp != NULL) {
        if (node_baru -> nilai == temp -> nilai) {
          cout << "Nilai Sudah Ada," <<
            "Masukkan Nilai Lain!" << endl;
          return;
        } else if ((node_baru -> nilai < temp -> nilai) && (temp -> kiri == NULL)) {
          temp -> kiri = node_baru;
          cout << "Nilai Di Sisipkan Di Sebelah Kiri" << endl;
          break;
        } else if (node_baru -> nilai < temp -> nilai) {
          temp = temp -> kiri;
        } else if ((node_baru -> nilai > temp -> nilai) && (temp -> kanan == NULL)) {
          temp -> kanan = node_baru;
          cout << "Nilai Di Sisipkan Di Sebelah Kanan" << endl;
          break;
        } else {
          temp = temp -> kanan;
        }
      }
    }
  }
  	pohonNode* insertRecursive(pohonNode *r, pohonNode *node_baru)
	{
		if(r==NULL)
		{
			r=node_baru;
			cout <<"Penyisipan Berhasil"<<endl;
			return r;
		}
	
		if(node_baru->nilai < r->nilai)
		{
			r->kiri = insertRecursive(r->kiri,node_baru);
		}
		else if (node_baru->nilai > r->nilai)  
		{
			r->kanan = insertRecursive(r->kanan,node_baru);
		}
	   else
	   {
	     	cout << "Nilai Duplikat Tidak Diperbolehkan" << endl;
	     	return r; 
		}
		return r;
	}

  void print2D(pohonNode * r, int space) {
    if (r == NULL)
      return;
    space += SPACE; // Tingkatkan jarak antar level
    print2D(r -> kanan, space); // Memproses child dari yang kanan dulu
    cout << endl;
    for (int i = SPACE; i < space; i++)
      cout << " ";
    cout << r -> nilai << "\n";
    print2D(r -> kiri, space); // Memproses dari yang kiri
  }

  void printPreorder(pohonNode * r) //(node saat ini, kiri, kanan) 
  {
    if (r == NULL)
      return;
    /* Mencetak Data Node Pertama */
    cout << r -> nilai << " ";
    /* Kemudian berulang di subtree kiri */
    printPreorder(r -> kiri);
    /* Sekarang berulang di subtree Kanan */
    printPreorder(r -> kanan);
  }

  void printInorder(pohonNode * r) //  (kiri, node saat ini, kanan)
  {
    if (r == NULL)
      return;
    /* Perulangan pertama pada child sebelah kiri */
    printInorder(r -> kiri);
    /* Kemudian mencetak Data Node Pertama */
    cout << r -> nilai << " ";
    /* Sekaranh melakukan perulangan pada child sebelah kanan */
    printInorder(r -> kanan);
  }
  void printPostorder(pohonNode * r) //(kiri, kanan, Root)
  {
    if (r == NULL)
      return;
    // Perulangan pertama pada subtree sebelah kiri
    printPostorder(r -> kiri);
    // Kemudian perulangan pada subtree sebelah kiri
    printPostorder(r -> kanan);
    // Mencetak node 
    cout << r -> nilai << " ";
  }

  pohonNode * iterativeSearch(int v) {
    if (root == NULL) {
      return root;
    } else {
      pohonNode * temp = root;
      while (temp != NULL) {
        if (v == temp -> nilai) {
          return temp;
        } else if (v < temp -> nilai) {
          temp = temp -> kiri;
        } else {
          temp = temp -> kanan;
        }
      }
      return NULL;
    }
  }

  pohonNode * recursiveSearch(pohonNode * r, int val) {
    if (r == NULL || r -> nilai == val)
      return r;

    else if (val < r -> nilai)
      return recursiveSearch(r -> kiri, val);

    else
      return recursiveSearch(r -> kanan, val);
  }

  int height(pohonNode * r) {
    if (r == NULL)
      return -1;
    else {
      /* Menghitung tinggi dari setiap subtree */
      int lheight = height(r -> kiri);
      int rheight = height(r -> kanan);

      /* Menggunakan nilai yang paling besar */
      if (lheight > rheight)
        return (lheight + 1);
      else return (rheight + 1);
    }
  }

  /* Mencatak node yang sudah diberi level */
  void printGivenLevel(pohonNode * r, int level) {
    if (r == NULL)
      return;
    else if (level == 0)
      cout << r -> nilai << " ";
    else // level > 0  
    {
      printGivenLevel(r -> kiri, level - 1);
      printGivenLevel(r -> kanan, level - 1);
    }
  }
  void printLevelOrderBFS(pohonNode * r) {
    int h = height(r);
    for (int i = 0; i <= h; i++)
      printGivenLevel(r, i);
  }

  pohonNode * minnilaiNode(pohonNode * node) {
    pohonNode * current = node;
    /* Loop kebawah untuk menemukan leaf paling kiri */
    while (current -> kiri != NULL) {
      current = current -> kiri;
    }
    return current;
  }

  pohonNode * deleteNode(pohonNode * r, int v) {
    if (r == NULL) {
      return NULL;
    }
    // Jika key yang akan dihapus lebih kecil dari key root, 
    // kemudian letakkan subtree di sebelah kiri
    else if (v < r -> nilai) {
      r -> kiri = deleteNode(r -> kiri, v);
    }
    // Jika key yang akan dihapus lebih besar dari key root, 
    // kemudian letakkan subtree di sebelah kanan
    else if (v > r -> nilai) {
      r -> kanan = deleteNode(r -> kanan, v);
    }
    // Jika key nya sama dengan key root, maka Ini adalah node yang akan dihapus 
    else {
      // node dengan satu child atau tidak sama sekali
      if (r -> kiri == NULL) {
        pohonNode * temp = r -> kanan;
        delete r;
        return temp;
      } else if (r -> kanan == NULL) {
        pohonNode * temp = r -> kiri;
        delete r;
        return temp;
      } else {
      	// Node dengan dua child: Dapatkan penerus inorder (terkecil di subtree sebelah kanan)
        pohonNode * temp = minnilaiNode(r -> kanan);
        // Salin data penerus inorder ke node ini
        r -> nilai = temp -> nilai;
        // Hapus penerus inorder
        r -> kanan = deleteNode(r -> kanan, temp -> nilai);
        //deleteNode(r->kanan, temp->nilai); 
      }
    }
    return r;
  }

};

int main() {
  BST obj;
  int option, val;

  do {
  	cout<<endl;
    cout << "Pilih Operasi Yang Di Inginkan " <<
      " Pilih Angka. Ketik 0 Untuk Keluar." << endl;
    cout << "1. Masukkan Node" << endl;
    cout << "2. Cari Node" << endl;
    cout << "3. Hapus Node" << endl;
    cout << "4. Print/Traversal Nilai BST" << endl;
    cout << "5. Height of Tree" << endl;
    cout << "6. Clear Screen" << endl;
    cout << "0. Exit Program" << endl;
	cout << "Masukkan Angka : ";
	
    cin >> option;
    cout<<endl;
    //Node n1;
    pohonNode * node_baru = new pohonNode();

    switch (option) {
    case 0:
      break;
    case 1:
      	cout <<"MASUKKAN NILAI"<<endl;
	      cout <<"Masukkan Nilai Dari TREE NODE Untuk Di Masukkan Dalam BST: ";
	      cin >> val;
	      node_baru->nilai = val;
	      obj.root= obj.insertRecursive(obj.root,node_baru);
	      //obj.insertNode(node_baru);
	      cout<<endl;
    		break;
      
    case 2:
      cout << "CARI" << endl;
      cout << "Masukkan Nilai Dari TREE NODE Yang Ingin Dicari Dalam BST:  ";
      cin >> val;
      //node_baru = obj.iterativeSearch(val);
      node_baru = obj.recursiveSearch(obj.root, val);
      if (node_baru != NULL) {
        cout << "Nilai Ditemukan" << endl;
      } else {
        cout << "Nilai Tidak Ditemukan" << endl;
      }
      break;
    case 3:
      cout << "HAPUS" << endl;
      cout << "Masukkan Nilai Dari TREE NODE Yang Ingin Dihapus Dalam BST: ";
      cin >> val;
      node_baru = obj.iterativeSearch(val);
      if (node_baru != NULL) {
        obj.deleteNode(obj.root, val);
        cout << "Nilai Dihapus" << endl;
      } else {
        cout << "Nilai Tidak Ditemukan" << endl;
      }
      break;
    case 4:
      cout << "PRINT 2D: " << endl;
      obj.print2D(obj.root, 5);
      cout << endl;
      cout << "Print Level Order BFS: \n";
      obj.printLevelOrderBFS(obj.root);
      cout << endl;
      cout <<"PRE-ORDER: ";
      obj.printPreorder(obj.root);
      cout<<endl;
      cout <<"IN-ORDER: ";
      obj.printInorder(obj.root);
      cout<<endl;
      cout <<"POST-ORDER: ";
      obj.printPostorder(obj.root);
      break;
    case 5:
      cout << "TREE HEIGHT" << endl;
      cout << "Height : " << obj.height(obj.root) << endl;
      break;
    case 6:
      system("cls");
      break;
    default:
      cout << "Masukkan Angka Yang Sesuai " << endl;
    }

  } while (option != 0);

  return 0;
}
